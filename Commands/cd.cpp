#include "cd.hpp"

cd::cd()
: last_directory(nullptr) {}

std::string cd::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (args.size() > 1) {
        return "\033[1;91mcd: too many arguments.\033[0m";
    }
    if (opts.size() > 1) {
        return "\033[1;91mcd: this version doesn't support any option, besides --help\033[0m";
    }
    if (opts.size() == 1) {
        if (opts[0] == "--help") {
            return "\033[1;97m"s + 
            R"(
                cd: Change the shell working directory.
        
                Change the current directory to DIR.  The default DIR is the value of the
                HOME shell variable.

                This version doesn't support options.
                `..' is processed by removing the immediately previous pathname component
                back to a slash or the beginning of DIR.

            )" + "\033[0m"s;
        } else if(opts[0] == "-") {
            if (last_directory) {
                std::swap(last_directory, dir);
                return "";
            }
            return "\033[1;91mcd: OLDPWD not set.\033[0m";
        } else {
            return "\033[1;91mcd: invalid option -- " + opts[0] + "\nTry 'cd --help' for more information.\033[0m";
        }
    }
    if (args.size() == 0) {
        while (dir->getParent()) {
            dir = dir->getParent();
        }
        auto new_dir = dir->find_dir("home");
        if (new_dir == nullptr) {
            return "\033[1;91mcd: Cannot access, 'home' directory doesn't exist.\033[0m";
        }
        dir = new_dir;
        new_dir = dir->find_dir(System::getCurrentUser()->getName());
        if (new_dir == nullptr) {
            return "\033[1;91mcd: Cannot access, '" + System::getCurrentUser()->getName() + "' doesn't exist.\033[0m";
        }
        dir = new_dir;
        return "";
    }
    if (args.size() == 1 && args[0] == "/") {
        while (dir->getParent()) {
            dir = dir->getParent();
        }
        return "";
    }
    std::vector<std::string> path;
    std::stringstream ss(args[0]);
    std::string current;
    int absalute = 0;
    if (ss.str().size() > 1 && ss.str()[0] == '/') {
        while (dir->getParent()) {
            dir = dir->getParent();
        }
        ++absalute;
    } 
    while (std::getline(ss, current, '/')) {
        path.push_back(current);
    }
    last_directory = dir;
    for (int i = 0 + absalute; i < path.size(); ++i) {
        if (i == 0 && path[i] == ".") {
            continue;
        }
        if (path[i] == "..") {
            if (dir->getName() != "/") {
                dir = dir->getParent();
                continue;
            }
            return "\033[1;91mcd: ../: Is a directory.\033[0m"; 
        }
        if (dir->find_file(path[i]) != nullptr) {
            return "\033[1;91mcd: " + path[i] + " Not a directory.\033[0m";
        }
        if (dir->find_dir(path[i]) == nullptr) {
            return "\033[1;91mcd: No such file or directory.\033[0m";
        } else {
            dir = dir->find_dir(path[i]);
        }
    }
    return "";
}
