#include "history.hpp"

std::string history::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!opts.empty()) {
        if (opts.size() > 1) {
            return "\033[1;91m history: too many options. \033[0m";
        }
        if (opts[0] == "--help") {
            return "\033[1;97m"s + 
                R"(
                    history: history [-c] 
                        Display or manipulate the history list.

                        -c	clear the history list by deleting all of the entries
                        --help     display this help and exit

                )" + "\033[0m"s;        
        } else if (opts[0] == "-c") {
            throw "clear";
        }
    }
    return args[0];
}
