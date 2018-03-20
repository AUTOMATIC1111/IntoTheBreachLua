#ifndef __FILE_H__
#define __FILE_H__

#include <windows.h>
#include <string>
#include <map>

struct Blob :public IStream {
	unsigned char *data;
	int length;

	std::string source;

	Blob();
	~Blob();

	int position;

	void reset() {
		position = 0;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,_COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject);
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE Read(_Out_writes_bytes_to_(cb, *pcbRead)  void *pv,_In_  ULONG cb,_Out_opt_  ULONG *pcbRead);
	HRESULT STDMETHODCALLTYPE Write(_In_reads_bytes_(cb)  const void *pv,_In_  ULONG cb,_Out_opt_  ULONG *pcbWritten);
	HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER dlibMove,DWORD dwOrigin,_Out_opt_  ULARGE_INTEGER *plibNewPosition);
	HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER libNewSize);
	HRESULT STDMETHODCALLTYPE CopyTo(_In_  IStream *pstm, ULARGE_INTEGER cb, _Out_opt_  ULARGE_INTEGER *pcbRead, _Out_opt_  ULARGE_INTEGER *pcbWritten);
	HRESULT STDMETHODCALLTYPE Commit(DWORD grfCommitFlags);
	HRESULT STDMETHODCALLTYPE Revert(void);
	HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER libOffset,ULARGE_INTEGER cb,DWORD dwLockType);
	HRESULT STDMETHODCALLTYPE Stat(__RPC__out STATSTG *pstatstg,DWORD grfStatFlag);
	HRESULT STDMETHODCALLTYPE Clone(__RPC__deref_out_opt IStream **ppstm);
};

struct BlobFromFile :public Blob {
	BlobFromFile(const std::string & filename);
};

struct ResourceDatFile {
	struct FileInfo {
		size_t offset;
		size_t size;

		FileInfo() {
			offset = 0;
			size = 0;
		}
		FileInfo(size_t o, size_t s) {
			offset = o;
			size = s;
		}
	};

	std::string filename;
	std::map<std::string, FileInfo> index;

	ResourceDatFile(const std::string & filename);

	void reload();
};

struct BlobFromResourceDat :public Blob {
	BlobFromResourceDat(const ResourceDatFile *dat,const std::string & filename);
};

#endif
