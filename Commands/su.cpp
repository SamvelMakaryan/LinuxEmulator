#include "su.hpp"

std::string su::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {
        if (args.size() > 1) {
            return "\033[1;91msu: Too many operands for su.\033[0m";
        }
        auto user = System::FindUser(args[0]);
        if (user != nullptr) {
            System::setCurrentUser(user);
            return "";
        } else {
            return "\033[1;91msu: user '" + args[0] + "' does not exist or the user entry does not contain all the required fields.\033[0m]";
        }
    } else {
        if (opts.empty()) {
            System::setCurrentUser(System::FindUser("root"));
            return "";
        }
        if (opts.size() > 1) {
            return "\033[1;91msu: This version doesn't support options besides --help.\033[0m";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help" || opts[0] == "-h") {
                return "\033[1;97m"s + 
                R"(
                    su: Change the effective user ID to that of <user>.
            
                    -h, --help                      display this help
                    -V, --version                   display version

                )" + "\033[0m"s;       
            } else if (opts[0] == "--version" || opts[0] == "-V") {
                return "\033[1;97msu version 1.00\nWritten by Samvel Makaryan.\033[0m";
            } else {
                return "\033[1;91msu: invalid option -- " + opts[0] + "\nTry 'su --help' for more information.\033[0m";
            }
        }      
    }
    return "";
}