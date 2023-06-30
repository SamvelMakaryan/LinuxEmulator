#include "mkdir.hpp"

std::string mkdir::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {
        bool verbose = false;
        bool parent = false;
        bool mode = false;
        char user;
        char group;
        char other;
        for (auto& i : opts) {
            if (i == "-v" || i == "--verbose") {
                verbose = true;
            } else if (i == "-p" || i == "--parents") {
                parent = true;
            } else if (i.size() == 5 || i[1] == 'm') {
                mode = true;
                user = i[2];
                group = i[3];
                other = i[4];
                if ((i[2] < '0' || i[2] > '7') || (i[3] < '0' || i[3] > '7') || (i[4] < '0' || i[4] > '7')) {
                    return "\033[1;91mmkdir: invalid mode ‘" + i.substr(2) + "'\033[0m";
                }
            } else {
                return "\033[1;91mmkdir: invalid option -- " + i + "\nTry 'mkdir --help' for more information.\033[0m";
            }
        }
        for (auto& i : args) {
            std::stringstream ss(i);
            std::vector<std::string> path;
            std::string cur;
            int cd_count = 0;
            while (std::getline(ss, cur, '/')) {
                path.push_back(cur);
            }
            if (parent) {
                for (int i = 0; i < path.size(); ++i) {
                    if (dir->find_dir(path[i]) != nullptr) {
                        return "\033[1;91mmkdir: cannot create directory " + path[i] + ": Directory exists\033[0m";
                    } else if (dir->find_file(path[i]) != nullptr) {
                        return "\033[1;91mmkdir: cannot create directory " + path[i] + ": File exists\033[0m";
                    } else {
                        if (verbose) {
                            std::cout << "\033[1;97mmkdir: created directory\033[0m\n";
                        }   
                        if (mode) {
                            dir->addSubDirectory(*new Directory(path[i], System::getCurrentUser()->getName(), dir->getGroupName(), dir, user - '0', group - '0', other - '0'));
                        } else {
                            dir->addSubDirectory(*new Directory(path[i], System::getCurrentUser()->getName(), dir->getGroupName(), dir, Permission::read | Permission::write | Permission::exexcute, Permission::read));
                        }
                        if (i != path.size() - 1) {
                            std::string cd_message = cd()({path[i]}, {}, dir);
                            if (cd_message != "") {
                                return cd_message;
                            }
                            ++cd_count;
                        } 
                    }
                }
                std::string cd_prev = "";
                while (cd_count-- != 0) {
                    cd_prev += "../";
                }
                cd()({cd_prev}, {}, dir);
            } else {
                for (int i = 0; i < path.size(); ++i) {
                    if (i == path.size() - 1) {
                        if (dir->find_dir(path[i]) != nullptr) {
                            return "\033[1;91mmkdir: cannot create directory " + path[i] + ": Directory exists.\033[0m";
                        } else if (dir->find_file(path[i]) != nullptr) {
                            return "\033[1;91mmkdir: cannot create directory " + path[i] + ": File exists.\033[0m";
                        } else {
                            if (verbose) {
                                std::cout << "\033[1;97mmkdir: created directory\033[0m\n";
                            }   
                            if (mode) {
                                dir->addSubDirectory(*new Directory(path[i], System::getCurrentUser()->getName(), dir->getGroupName(), dir, user - '0', group - '0', other - '0'));
                            } else {
                                dir->addSubDirectory(*new Directory(path[i], System::getCurrentUser()->getName(), dir->getGroupName(), dir, Permission::read | Permission::write | Permission::exexcute, Permission::read));
                            }
                        }
                    } else if (path[i] == ".") {
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
                std::string cd_prev = "";
                while (cd_count-- != 0) {
                    cd_prev += "../";
                }
                cd()({cd_prev}, {}, dir); 
            }
        }
    } else {
        if (opts.empty()) {
            return "\033[1;91mmkdir: missing operand\nTry 'mkdir --help' for more information.\033[0m";
        }
        else {
            if (opts.size() > 1) {
                return "\033[1;91mmkdir: without arguments can have only one option.\033[0m";
            } else {
                if (opts[0] == "--help") {
                    return "\033[1;97m"s + 
                    R"(
                    Usage: mkdir [OPTION]... DIRECTORY...
                    Create the DIRECTORY(ies), if they do not already exist.

                    -p, --parents     no error if existing, make parent directories as needed.
                    -v, --verbose     print a message for each created directory.
                    --help     display this help and exit.
                    --version  output version information and exit.
                    )" + "\033[0m"s;
                } else if (opts[0] == "--version") {
                    return "\033[1;97mmkdir version 1.00\nWritten by Samvel Makaryan.\033[0m";
                } else {
                    if (opts[0] == "-v" || opts[0] == "--verbose" || opts[0] == "-p" || opts[0] == "--parents") {
                        return "\033[1;91mmkdir: missing operand\nTry 'mkdir --help' for more information.\033[0m";    
                    }
                    return "\033[1;91mmkdir: invalid option -- " + opts[0] + "\nTry 'mkdir --help' for more information.\033[0m";
                }
            }
        }
    }
    return "";
}
 