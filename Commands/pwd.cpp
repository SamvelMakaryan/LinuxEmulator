#include "pwd.hpp"

std::string pwd::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    if (!opts.empty()) {
        if (opts.size() > 1) {
            return "\033[1;91mpwd: This version of pwd doesn't support any options besides --help.\033[0m"; 
        }
        if (opts[0] == "--help") {
            return "\033[1;97m\t\tpwd: pwd\n\n\t\tPrint the name of the current working directory.\n\n\t\tThis version of pwd doesn't support any options besides --help\033[0m";
        } 
        return "\033[1;91mpwd: invalid option -- " + opts[0] + "\nTry 'pwd --help' for more information.\033[0m";
    }
    std::string path = "/";
    auto current = dir;
    while (dir->getParent()) {
        path = dir->getName() + path;
        path = "/" + path;
        cd()({"../"}, {}, dir);
    }
    dir = current;
    if (path.size() > 1) {
        path.pop_back();
    }
    return path;
}
