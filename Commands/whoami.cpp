#include "whoami.hpp"

std::string whoami::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {   
        return "\033[1;91mwhoami: extra operand '" + args[0] + "'\nTry 'whoami --help' for more information.\033[0m";
    } else {
        if (opts.empty()) {
            return "\033[1;97m" + System::getCurrentUser()->getName() + "\033[0m";
        }
        if (opts.size() > 1) {
            return "\033[1;91mwhoami: this version doesn't support options besides --help, --version.\033[0m";
        }
        if (opts[0] == "--help") {
            return "\033[1;91"s +
            R"(
                Usage: whoami [OPTION]...
                Print the user name associated with the current effective user ID.

                --help     display this help and exit
                --version  output version information and exit
            )" + "\033[0m"s;
        } else if (opts[0] == "--version") {
            return "\033[1;97mmkdir version 1.00\nWritten by Samvel Makaryan.\033[0m";
        } else {
            return "\033[1;91mcd: invalid option -- " + opts[0] + "\nTry 'cd --help' for more information.\033[0m";
        }
    }
    return "";
}