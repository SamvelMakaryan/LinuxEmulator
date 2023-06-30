#include "useradd.hpp"

std::string useradd::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    bool home = false;
    for (auto& i : opts) {
        if (i == "-m" || i == "--create-home") {
            home = true;
        } else if (i == "--help") {
            continue;
        } else {
            return "\033[1;91museradd: invalid option -- " + i + "\nTry 'mkdir --help' for more information.\033[0m";
        }
    }
    if (!args.empty()) {
        for (auto& i : args) {
            if (System::FindUser(i) != nullptr) {
                return "\033[1;91museradd: user '" + i + "' already exists.\033[0m";
            }
            System::addUser(i);
            if (home) {
                auto prev_dir = dir;
                cd()({"/"}, {}, dir);
                mkdir()({"home/" + i}, {}, dir);
                dir = prev_dir;
            }
        }
    } else {
        if (opts.size() > 1) {
            return "\033[1;91m Too many options for useradd\033[0m";
        }
        if (opts.empty() || opts[0] == "--help" || home) {
            return "\033[1;97m"s + 
                R"(
                Usage: useradd [-m]

                Options:
                
                -m, --create-home             create the user's home directory
                    --help     display this help and exit.
                )" + "\033[0m"s;
        } else {
            return "\033[1;91museradd: unrecognized option"s + opts[0] + "\nTry 'rm --help' for more information.\033[0m"; 
        }
    }
    return "";
}
