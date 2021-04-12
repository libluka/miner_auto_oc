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
	LPSTR  largs = const_cast<char*>(args_temp.c_str());

	memset(&startup_info, 0, sizeof(startup_info));
	memset(&process_information, 0, sizeof(process_information));
	startup_info.cb = sizeof(startup_info);

	BOOL result = CreateProcessA(
		lpath,
		largs,
		0,
		0,
		FALSE,
		DETACHED_PROCESS,
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

bool file_exists(std::string& path) {
	LPCSTR path_l = path.c_str();

	if (GetFileAttributesA(path_l) == 0xFFFFFFFF) {
		return false;
	}

	return true;
}

DWORD get_process_id(std::string& p_name) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE list_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);;

	Process32First(list_snapshot, &entry);
	do {
		if(entry.szExeFile)

	} while (Process32Next(list_snapshot, &entry))
}