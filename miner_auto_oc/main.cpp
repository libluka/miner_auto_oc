#include <iostream>
#include <Windows.h>

#include "util.hpp"

#define MIN_PROFILE_NUM 1
#define MAX_PROFILE_NUM 5

const std::string __usage = "\nUsage: miner_auto_oc [-e] [-al] [-os] [-ot]\n\n"
"Options:\n"
"         -e       The path to the intended executable to be run (usually the miner).\n"
"         -al      The path to your afterburner executable.\n"
"         -os      The profile number you want active while the miner is active.     Must be between 1 & 5.\n"
"         -ot      The profile number you want reverted to when the miner is closed. Must be between 1 & 5.\n";

int main(int argc, char* argv[])
{
    std::string miner_path = "", afterburner_path = "";
    int profile_active = 0, profile_close = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.find("-") == std::string::npos && i + 1 == argc) {
            break;
        }
        else if (arg.find("-") != std::string::npos
            && i == argc - 1) {

            std::cerr << __usage;
            return -1;
        }

        if (arg == "-e") {
            miner_path = argv[i + 1];
        }
        if (arg == "-al") {
            afterburner_path = argv[i + 1];
        }
        if (arg == "-os") {
            profile_active = std::stoi(argv[i + 1]);
        }
        if (arg == "-ot") {
            profile_close = std::stoi(argv[i + 1]);
        }
    }

    if(afterburner_path == ""
        || miner_path == ""
        || !in_bound(profile_active, MIN_PROFILE_NUM, MAX_PROFILE_NUM)
        || !in_bound(profile_close,  MIN_PROFILE_NUM, MAX_PROFILE_NUM)) {

        std::cout << __usage;
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

    std::cout << "miner_path: " << miner_path << '\n';
    std::cout << "af_path: " << afterburner_path << '\n';
    std::cout << "profile_active: " << profile_active << '\n';
    std::cout << "profile_close: " << profile_close << '\n';
}