#include "blob.h"
#include <cstdio>
#include <vector>

Blob::Blob() {
	data = NULL;
	length = 0;
	position = 0;
	source = "<null>";
}


Blob::~Blob() {
	if(data != NULL)
		delete[] data;
}

HRESULT Blob::QueryInterface(REFIID riid, void ** ppvObject) {
	return E_NOTIMPL;
}

ULONG Blob::AddRef(void) {
	return 1;
}

ULONG Blob::Release(void) {
	return 0;
}

HRESULT Blob::Read(void * pv, ULONG cb, ULONG * pcbRead) {
	int count = min((int)cb, length - position);
	if(pcbRead) *pcbRead = count;

	memcpy(pv, data + position, count);
	position += count;

	return S_OK;
}

HRESULT Blob::Write(const void * pv, ULONG cb, ULONG * pcbWritten) {
	return E_NOTIMPL;
}

HRESULT Blob::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition) {
	int start;
	switch(dwOrigin) {
	case STREAM_SEEK_SET:
	default:
		start = 0;
		break;
	case STREAM_SEEK_CUR:
		start = position;
		break;
	case STREAM_SEEK_END:
		start = length;
		break;
	}

	start += (int) dlibMove.QuadPart;
	if(start >= length) start = length - 1;
	if(start < 0) start = 0;

	position = start;

	if(plibNewPosition) plibNewPosition->QuadPart = position;

	return S_OK;
}

HRESULT Blob::SetSize(ULARGE_INTEGER libNewSize) {
	return E_NOTIMPL;
}

HRESULT Blob::CopyTo(IStream * pstm, ULARGE_INTEGER cb, ULARGE_INTEGER * pcbRead, ULARGE_INTEGER * pcbWritten) {
	return E_NOTIMPL;
}

HRESULT Blob::Commit(DWORD grfCommitFlags) {
	return E_NOTIMPL;
}

HRESULT Blob::Revert(void) {
	return E_NOTIMPL;
}

HRESULT Blob::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) {
	return E_NOTIMPL;
}

HRESULT Blob::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) {
	return E_NOTIMPL;
}

HRESULT Blob::Stat(STATSTG * pstatstg, DWORD grfStatFlag) {
	pstatstg->type = STGTY_STREAM;
	pstatstg->cbSize.QuadPart = length;

	return S_OK;
}

HRESULT Blob::Clone(IStream ** ppstm) {
	return E_NOTIMPL;
}

BlobFromFile::BlobFromFile(const std::string & filename) {
	source = "file("+filename+")";

	FILE *file = fopen(filename.c_str(), "rb");
	if(file == NULL) return;

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	data = new unsigned char[size];
	length = size;

	fread(data, 1, size, file);

	fclose(file);
}

ResourceDatFile::ResourceDatFile(const std::string & filename) {
	this->filename = filename;

	reload();
}

void ResourceDatFile::reload() {
	index.clear();

	FILE *file = fopen(filename.c_str(), "rb");
	if(file == NULL) return;

	unsigned int indexSize = 0;
	fread(&indexSize, sizeof(indexSize), 1, file);

	unsigned int *indexOffsets = new unsigned int[indexSize];
	fread(indexOffsets, sizeof(indexOffsets[0]), indexSize, file);

	for(unsigned int i = 0; i < indexSize; i++) {
		unsigned int size, namesize;

		fseek(file, indexOffsets[i], SEEK_SET);
		fread(&size, sizeof(size), 1, file);
		fread(&namesize, sizeof(namesize), 1, file);

		std::vector<char> vec;
		vec.resize(namesize);
		fread(vec.data(), namesize, 1, file);
		std::string name(vec.begin(), vec.end());

		index[name] = FileInfo(ftell(file), size);
	}

	delete[] indexOffsets;

	fclose(file);
}

BlobFromResourceDat::BlobFromResourceDat(const ResourceDatFile *dat, const std::string & filename){
	if(dat == NULL) {
		source = "resource(<null>," + filename + ")";
		return;
	}
	source = "resource(" + dat->filename + "," + filename + ")";

	auto iter = dat->index.find(filename);
	if(iter == dat->index.end()) {
		return;
	}
	const ResourceDatFile::FileInfo &info = iter->second;
	
	FILE *file = fopen(dat->filename.c_str(), "rb");
	if(file == NULL) return;
	fseek(file, info.offset, SEEK_SET);

	data = new unsigned char[info.size];
	length = info.size;
	fread(data, 1, info.size, file);

	fclose(file);
}