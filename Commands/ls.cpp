#include "ls.hpp"

std::string ls::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    bool all = false;
    bool almost_all = false;
    bool long_version = false;
    for (auto& i : opts) {
        if (i == "-l" || i == "-la") {
            long_version = true;
        } else if (i == "-a" || i == "-la" || i == "--all") {
            all = true;
        } else if (i == "-A" || i == "--almost-all") {
            almost_all = true;
        } 
    }
    if (!args.empty()) {
        for (auto& i : args) {
            std::stringstream ss(i);
            std::vector<std::string> path;
            std::string cur;
            int cd_count = 0;
            while (std::getline(ss, cur, '/')) {
                path.push_back(cur);
            }
            for (int i = 0; i < path.size(); ++i) {
                if (path[i] == "." && path.size() > 1) {
                    continue;
                } else {
                    std::string cd_message = cd()({path[i]}, {}, dir);
                    if (cd_message != "") {
                        std::string cd_prev = "";
                        while (cd_count-- != 0) {
                            cd_prev += "../";
                        }
                        cd()({cd_prev}, {}, dir);
                        return cd_message;
                    }
                    ++cd_count;
                }
            }
            if (all && long_version) {
                std::cout << "\033[1;97m.\n..\n\033[0m";
                print_dir(*dir, [](Directory*){return true;}, true);    
                print_file(*dir, [](File*){return true;}, true);    
            } else if (almost_all && long_version) {
                print_dir(*dir, [](Directory*){return true;}, true);    
                print_file(*dir, [](File*){return true;}, true);    
            } else if (long_version) {
                print_dir(*dir, [](Directory* dir){return dir->getName()[0] != '.';}, true);
                print_file(*dir, [](File* file){return file->getName()[0] != '.';}, true);                
            } else if (all || (almost_all && all)) {
                std::cout << "\033[1;97m. .. \033[0m";
                print_dir(*dir, [](Directory*){return true;}, false);    
                print_file(*dir, [](File*){return true;}, false);    
            } else {
                print_dir(*dir, [](Directory*){return true;}, false);    
                print_file(*dir, [](File*){return true;}, false);    
            }
            std::string cd_prev = "";
            while (cd_count-- != 0) {
                cd_prev += "../";
            }
            cd()({cd_prev}, {}, dir);
        }
    } else {
        if (opts.empty()) {
            print_dir(*dir, [](Directory* dir){return dir->getName()[0] != '.';}, false);
            print_file(*dir, [](File* file){return file->getName()[0] != '.';}, false);
            return "";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help") {
                return "\033[1;97m"s +
                R"(
                    Usage: ls [OPTION]... [FILE]...
                    List information about the FILEs (the current directory by default).
                    Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

                    Mandatory arguments to long options are mandatory for short options too.
                    -a, --all                  do not ignore entries starting with .
                    -A, --almost-all           do not list implied . and ..
                    -l                         use a long listing format
                    --help     display this help and exit.
                    --version  output version information and exit.
                )" + "\033[0m"s;
            } else if (opts[0] == "--version") {
                return "\033[1;97mls version 1.00\nWritten by Samvel Makaryan.\033[0m";
            } else {
                if (!(all || almost_all || long_version)) {
                    
                    return "\033[1;91mls: invalid option -- " + opts[0] + "\nTry 'ls --help' for more information.\033[0m";
                }
            } 
        }
        if (all && long_version) {
            std::cout << "\033[1;97m.\n..\n\033[0m"; 
            print_dir(*dir, [](Directory*){return true;}, true);    
            print_file(*dir, [](File*){return true;}, true);    
        } else if (almost_all && long_version) { 
            print_dir(*dir, [](Directory*){return true;}, true);    
            print_file(*dir, [](File*){return true;}, true);    
        } else if (all && almost_all) {
            std::cout << "\033[1;97m. .. \033[0m"; 
            print_dir(*dir, [](Directory*){return true;}, false);    
            print_file(*dir, [](File*){return true;}, false);    
        } else if (long_version) {
            std::cout << "\033[1;97m.\n..\n\033[0m"; 
            print_dir(*dir, [](Directory* dir){return dir->getName()[0] != '.';}, true);
            print_file(*dir, [](File* file){return file->getName()[0] != '.';}, true);
        } else if (all) {
            std::cout << "\033[1;97m. .. \033[0m"; 
            print_dir(*dir, [](Directory*){return true;}, false);    
            print_file(*dir, [](File*){return true;}, false);    
        } else if (almost_all) {
            print_dir(*dir, [](Directory*){return true;}, false);    
            print_file(*dir, [](File*){return true;}, false);
        } else {
            return "\033[1;91mls: invalid option(s) -- \nTry 'ls --help' for more information.\033[0m";
        }
    }
    return "";
}


void ls::print_dir(Directory& dir, std::function<bool(Directory*)> p, bool is_long) const {
    for (auto& i : dir.getDirectories()) {
        if (p(i)) {
            if (is_long) {
                std::string permission(1, 'd');
                getPermission(permission, i->getUserPermission());
                getPermission(permission, i->getGroupPermission());
                getPermission(permission, i->getOtherPermission());
                std::cout << "\033[1;97m" << permission << "  " << i->getUserName() << "  " << i->getGroupName() << "  \033[94m" << i->getName() << "\033[0m\n"; 
            } else {
                std::cout << "\033[1;94m" << i->getName() << "  " << "\033[0m";
            }
        }
    }
    if (!dir.getDirectories().empty()) {
        std::cout << std::endl;
    }
}

void ls::print_file(Directory& dir, std::function<bool(File*)> p, bool is_long) const {
    for (auto& i : dir.getFiles()) {
        if (p(i)) {
            if (is_long) {
                std::string permission(1, '-');
                getPermission(permission, i->getUserPermission());
                getPermission(permission, i->getGroupPermission());
                getPermission(permission, i->getOtherPermission());
                std::cout << "\033[1;97m" << permission << "  " << i->getUserName() << "  " << i->getGroupName() <<  "  " << i->getName() << "\033[0m\n"; 
            } else {
                std::cout << "\033[1;97m" << i->getName() << "  " << "\033[0m";
            }
        }
    }
    if (!dir.getFiles().empty()) {
        std::cout << std::endl;
    }
}

void ls::getPermission(std::string& per, int permission) const {
    switch (permission) {
    case 0:
        per += "---";
        break;
    case 1:
        per += "--x";
        break;
    case 2:
        per += "-w-";
        break;
    case 3:
        per += "-wx";
        break;
    case 4:
        per += "r--";
        break;
    case 5:
        per += "r-x";
        break;
    case 6:
        per += "rw-";
        break;
    case 7:
        per += "rwx";
        break;
    default:
        per += "---";
    }    
}
