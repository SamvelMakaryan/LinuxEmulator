#include "chmod.hpp"

std::string chmod::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    bool verbose = false;
    bool changes = false;
    bool recursive = false;
    bool minus = false;
    bool set_mode = false;
    int user = 0;
    int group = 0;
    int other = 0;
    for (auto& i : opts) {
        if (i == "-v" || i == "--verbose") {
            verbose = true;
        } else if (i == "-c" || i == "--changes") {
            changes = true;
        } else if (i == "-R" || i == "--recursive") {
            recursive = true;
        } else if (i == "--help" || i == "--version") {
            continue;
        } else if (i.size() > 1 && (i[1] == 'x' || i[1] == 'w' || i[1] == 'r')) {
            minus = true;
            for (auto& m : i) {
                if (m == '-') {
                    continue;
                }
                if (m == 'r') {
                    user += 4;
                    group += 4;
                    other += 4;
                } else if (m == 'w') {
                    user += 2;
                    group += 2;
                    other += 2;
                } else if (m == 'x') {
                    user += 1;
                    group += 1;
                    other += 1;
                } else {
                    return "\033[1;91mchmod: invalid mode: '" + i + "'\033[0m";
                }
            }
        } else {
            return "\033[1;91mchmod: unrecognized option" + i + "\nTry 'chmod --help' for more infochmodation.\033[0m";
        }
    }
    if (!args.empty()) {
        std::string mode = args[0];
        if (!minus) {
            if (mode[0] == '+') {
                for (auto& m : mode) {
                    if (m == '+') {
                        continue;
                    }
                    if (m == 'r') {
                        user += 4;
                        group += 4;
                        other += 4;
                    } else if (m == 'w') {
                        user += 2;
                        group += 2;
                    } else if (m == 'x') {
                        user += 1;
                        group += 1;
                        other += 1;
                    } else {
                        return "\033[1;91mchmod: invalid mode: '" + mode + "'\033[0m";
                    }
                }
            } else {
                set_mode = true;
                if (mode.size() > 3) {
                    return "\033[1;91mchmod: invalid mode: '" + mode + "'\033[0m";
                }
                for (int i = mode.size() - 1; i >= 0; --i) {
                    if ((mode[i] < '0' || mode[i] > '7')) {
                        return "\033[1;91mchmod: invalid mode: '" + mode + "'\033[0m";
                    }
                    if (i == mode.size() - 1) {
                        other = mode[i] - '0';
                    } else if (i == mode.size() - 2) {
                        group = mode[i] - '0';
                    } else if (i == mode.size() - 3) { 
                        user = mode[i] - '0';
                    }
                }
            }
        }
        for (auto& i : args) {
            if (!minus && (i == args[0])) {
                continue;
            }
            std::stringstream ss(i);
            std::vector<std::string> path;
            std::string cur;
            int cd_count = 0;
            while (std::getline(ss, cur, '/')) {
                path.push_back(cur);
            }
            if (recursive) {
/////rec        
            } else {
                for (int i = 0; i < path.size(); ++i) {
                    if (i == path.size() - 1) {
                        FileSystemComponent* mode_file = dir->find_file(path[i]);
                        if (!mode_file) {
                            mode_file = dir->find_dir(path[i]);
                        }
                        if (!mode_file) {
                            return "\033[1;91mchmod: cannot access '" + path[i] + "': No such file or directory\033[0m";
                        }
                        int cur_user_perm;
                        int cur_group_perm;
                        int cur_other_perm;
                        cur_user_perm = mode_file->getUserPermission();
                        cur_group_perm = mode_file->getGroupPermission();
                        cur_other_perm = mode_file->getOtherPermission();
                        if (minus) {
                            mode_file->removeUserPermission(user);
                            mode_file->removeGroupPermission(group);
                            mode_file->removeOtherPermission(other);
                        } else if (set_mode) {
                            mode_file->setUserPermission(user);
                            mode_file->setGroupPermission(user);
                            mode_file->setOtherPermission(user);
                        } else {
                            mode_file->addUserPermission(user);
                            mode_file->addGroupPermission(group);
                            mode_file->addOtherPermission(other);
                        }
                        if (verbose || (changes && ((cur_user_perm != mode_file->getUserPermission())
                            || (cur_group_perm != mode_file->getGroupPermission())  || (cur_other_perm != mode_file->getOtherPermission())))) {
                            std::cout << "\033[1;97mmode of '" << path[i] << "' changed from "  << cur_user_perm << cur_group_perm << cur_other_perm 
                                      << " to " << mode_file->getUserPermission() << mode_file->getGroupPermission() <<  mode_file->getOtherPermission() << "\n\033[0m";
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
            return "\033[1;91mchmod: missing operand.\nTry 'chmod --help' for more information.\033[0m";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help") {
                return "\033[1;97m"s + 
                R"(
                    Usage: chmod [OPTION]... MODE[,MODE]... FILE...
                      or:  chmod [OPTION]... OCTAL-MODE FILE...
                    Change the mode of each FILE to MODE.

                      -c, --changes          like verbose but report only when a change is made
                      -v, --verbose          output a diagnostic for every file processed
                      -R, --recursive        change files and directories recursively
                          --help     display this help and exit
                          --version  output version information and exit

                )" + "\033[0m"s;
            }
            if (opts[0] == "--version") {
                return "\033[1;97mchmod version 1.00\nWritten by Samvel Makaryan.\033[0m";
            }
            return "\033[1;91mchmod: missing operand.\033[0m";
        }
        return "\033[1;91mchmod: invalid optons for chmod without operands.\033[0m";
    }
    return "";
}

