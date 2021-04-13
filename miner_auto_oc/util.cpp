#include "util.hpp"
#include <iostream>
#include <TlHelp32.h>

/*pid from started instance of afterburner may be invalid if it is already open*/
/*pid will be found later for monitoring*/
bool execute_application(std::string path, std::string args) {
	STARTUPINFOA startup_info;
	PROCESS_INFORMATION process_information;

	LPCSTR lpath = path.c_str();

	std::string args_temp = path + " " + args;
	LPSTR largs = const_cast<char*>(args_temp.c_str());

	ZeroMemory(&startup_info,		 sizeof(STARTUPINFOA));
	ZeroMemory(&process_information, sizeof(PROCESS_INFORMATION));
	startup_info.cb = sizeof(STARTUPINFOA);

	BOOL result = CreateProcessA(
		lpath,
		largs,
		0,
		0,
		FALSE,
		CREATE_NEW_CONSOLE,
		0,
		0,
		&startup_info,
		&process_information
	);

	CloseHandle(process_information.hProcess);
	CloseHandle(process_information.hThread);

	return result;
}

bool apply_profile(std::string path, int profile_num) {
	std::string arg_f = "-Profile" + std::to_string(profile_num);
	return execute_application(path, arg_f);
}

bool in_bound(int num, int min_bound, int max_bound) {
	return !(num < min_bound || num > max_bound);
}

bool file_exists(std::string path) {
	LPCSTR path_l = path.c_str();

	if (GetFileAttributesA(path_l) == 0xFFFFFFFF) {
		return false;
	}

	return true;
}

DWORD get_process_id_by_path(std::string path) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE list_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
	std::wstring base_filename_w = std::wstring(base_filename.begin(), base_filename.end());
	

	Process32First(list_snapshot, &entry);
	do {
		if (wcscmp(entry.szExeFile, base_filename_w.c_str()) == 0) {
			CloseHandle(list_snapshot);

			return entry.th32ProcessID;
		}

	} while (Process32Next(list_snapshot, &entry));
	
	CloseHandle(list_snapshot);
	return 0;
}