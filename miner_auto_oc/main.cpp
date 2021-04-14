#include <iostream>
#include <Windows.h>

#include "getopt.h"
#include "util.hpp"

#define MIN_PROFILE_NUM 1
#define MAX_PROFILE_NUM 5

const std::string __usage = "\nUsage: miner_auto_oc [-e] [-a] [-o] [-c]\n\n"
"Options:\n"
"         -h       Shows this help page.\n"
"         -e       The path to the intended executable to be run (usually the miner).\n"
"         -a       The path to your afterburner executable.\n"
"         -o       The profile number you want active on open (while the miner is active). Must be between 1 & 5.\n"
"         -c       The profile number you want reverted to when the miner is closed.       Must be between 1 & 5.\n";

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cerr << "\nType miner_auto_oc [-h] for help.\n";
        return -1;
    }

    std::string miner_path = "", afterburner_path = "";
    int profile_active = 0, profile_close = 0;

    DWORD miner_process_id = 0;

    int index;
    while ((index = getopt_a(argc, argv, "e:a:o:c:h")) != -1) {
        switch (index) {
        case 'e':
            miner_path = optarg_a;
            break;

        case 'a':
            afterburner_path = optarg_a;
            break;

        case 'o':
            profile_active = std::stoi(optarg_a);
            break;

        case 'c':
            profile_close = std::stoi(optarg_a);
            break;

        case 'h':
            std::cerr << __usage;
            return -1;
        }
    }

    if(!in_bound(profile_active, MIN_PROFILE_NUM, MAX_PROFILE_NUM)
        || !in_bound(profile_close,  MIN_PROFILE_NUM, MAX_PROFILE_NUM)) {

        std::cerr << "\nOut of bound profile number!\n";
        return -1;

    }
    else if (!file_exists(miner_path) || miner_path.find(".exe") == std::string::npos) {
        std::cerr << "\nInvalid miner path!\n";
        return -1;
    }
    else if (!file_exists(afterburner_path) || afterburner_path.find(".exe") == std::string::npos) {
        std::cerr << "\nInvalid afterburner path!\n";
        return -1;
    }

    std::cout << "\nExecuting specified executable (" << miner_path << ")\n";
    execute_application(miner_path, "");

    miner_process_id = get_process_id_by_path(miner_path);

    std::cout << "miner_path: " << miner_path << '\n';
    std::cout << "af_path: " << afterburner_path << '\n';
    std::cout << "profile_active: " << profile_active << '\n';
    std::cout << "profile_close: " << profile_close << '\n';
    std::cout << "miner_pid: " << miner_process_id << '\n';

    std::cout << "\nSetting afterburner to profile " << profile_active << "!\n";
    apply_profile(afterburner_path, profile_active);

    std::cout << "Awaiting miner process close...\n";

    HANDLE miner_handle = OpenProcess(SYNCHRONIZE, TRUE, miner_process_id);
    WaitForSingleObject(miner_handle, INFINITE);

    std::cout << "\nProcess closed! Applying profile " << profile_close << "!\n";
    apply_profile(afterburner_path, profile_close);

    std::cout << "Unregistering handle...\n";
    CloseHandle(miner_handle);

    std::cout << "Success! Exit code 0\n";

    return 0;
}