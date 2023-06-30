#include "userdel.hpp"

std::string userdel::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {
        for (auto& i : args) {
            if (i == "root") {
                return "\033[1;91museradd: Cannot delete root user.\033[0m";
            }
            if (i == System::getCurrentUser()->getName()) {
                return "\033[1;91museradd: Cannot delete current user.\033[0m";
            }
            if (System::FindUser(i) == nullptr) {
                return "\033[1;91museradd: user '" + i + "' doesn't exists.\033[0m";
            }
            System::removeUser(i);
        }
    } else {
        if (opts.size() > 1) {
            return "\033[1;91m Too many options for useradd\033[0m";
        }
        if (opts.empty() || opts[0] == "--help") {
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