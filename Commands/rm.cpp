#include "rm.hpp"

std::string rm::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    bool verbose = false;
    bool recursive = false;
    bool directory = false;
    for (auto& i : opts) {
        if (i == "-r" || i == "-R" || i == "--recursive") {
            recursive = true;
        } else if (i == "-v" || i == "--verbose") {
            verbose = true;
        } else if (i == "-d" || i == "--dir") {
            directory = true;
        } else if (i == "--help" || i == "--version") {
            continue;
        } else {
            return "\033[1;91mrm: unrecognized option"s + i + "\nTry 'rm --help' for more information.\033[0m";
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
            if (recursive) {
                if (directory) {
                    return "\033[1;91m -d(--dir) and -r(-R, --recursive) options are incompatible.\033[0m";
                }
                for (int i = 0; i < path.size(); ++i) {
                    if (i == path.size() - 1) { 
                        dir->clear(); 
                    } else if (path[i] == "." ) {
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
                    std::string cd_prev = "";   
                    while (cd_count-- != 0) {
                        cd_prev += "../";
                    }
                    cd()({cd_prev}, {}, dir);
                }
            } else {
                for (int i = 0; i < path.size(); ++i) {
                    if (path[i] == ".") {
                        continue;
                    }
                    if (i == path.size() - 1) {
                        if (!directory) {
                            if (dir->find_dir(path[i]) != nullptr) {
                                return "\033[1;91mrm cannot remove '" + path[i] + "' Is a directory.\033[0m";
                            } 
                            if (dir->find_file(path[i]) == nullptr) {
                                return "\033[1;91mrm: cannot remove '" + path[i] + "': No such file or directory.\033[0m";
                            }
                            if (verbose) {
                                std::cout << "\033[1;97mrm: removed '" + path[i] + "'\033[0m\n";
                            }
                            dir->removeFile(path[i]);
                        } else {
                            if (dir->find_file(path[i]) != nullptr) {
                                if (verbose) {
                                    std::cout << "\033[1;97mrm: removed '" + path[i] + "'\033[0m\n";
                                }
                                dir->removeFile(path[i]);
                                continue;
                            }
                            if (dir->find_dir(path[i]) != nullptr) {
                                if (!(dir->find_dir(path[i])->is_files_empty()) || !(dir->find_dir(path[i])->is_directories_empty())) {
                                    return "\033[1;91mrm: failed to remove '" + path[i] + "' Directory not empty.\033[0m";
                                }
                                if (verbose) {
                                    std::cout << "\033[1;97mrm: removed directory '" + path[i] + "'\033[0m\n";
                                }
                                dir->removeSubDirectory(path[i]);
                                continue;
                            }
                            return "\033[1;91mrm: cannot remove '" + path[i] + "': No such file or directory.\033[0m";
                        }
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
            return "\033[1;91mrm: missing operand.\nTry 'rm --help' for more information.\n\033[0m";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help") {
                return "\033[1;97m"s + 
                R"(
                    Usage: rm [OPTION]... [FILE]...
                    Remove the FILE(s).

                    -r, -R, --recursive   remove directories and their contents recursively
                    -d, --dir             remove empty directories
                    -v, --verbose         explain what is being done
                        --help     display this help and exit
                        --version  output version information and exit

                )" + "\033[0m"s;
            }
            if (opts[0] == "--version") {
                return "\033[1;97mcat version 1.00\nWritten by Samvel Makaryan.\033[0m";
            }
            return "\033[1;91mrm: missing operand.\033[0m";
        }
        return "\033[1;91mrm: invalid optons for rm without operands.\033[0m";
    }
    return "";
}
