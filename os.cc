#include "os.h"
#include "utils.h"

#include <shlobj.h>
#pragma comment(lib, "shell32.lib")

namespace OS {

std::string getKnownFolder(int csild) {
	char folder[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, csild, NULL, SHGFP_TYPE_CURRENT, folder);

	if(result != S_OK)
		return "";

	return folder;
}

void log(const std::string & line) {
	::log("%s\n", line.c_str());
}

bool isshiftdown() {
	return (GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0x8000;
}

double mtime(const std::string filename) {
	struct stat st = { 0 };
	stat(filename.c_str(), &st);

	return (double) st.st_mtime;
}

void mkdir(std::string path) {
	SHCreateDirectoryEx(NULL, s2ws(path).c_str(), NULL);
}

}
