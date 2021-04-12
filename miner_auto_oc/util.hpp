#include <string>
#include <Windows.h>

bool apply_profile(std::string, int);
bool execute_application(std::string, std::string);

bool in_bound(int, int, int);
bool file_exists(std::string&);
DWORD get_process_id(std::string&);