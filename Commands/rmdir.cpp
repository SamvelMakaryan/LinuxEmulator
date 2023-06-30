#include "rmdir.hpp"

std::string rmdir::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    bool parent = false;
    bool verbose = false;
    for (auto& i : opts) {
        if (i == "-p" || i == "--parents") {
            parent = true;
        } else if (i == "-v" || "--verbose") {
            verbose = true;
        } else if (i == "--help" || i == "--version") {
            continue;
        } else {
            return "\033[1;91mrmdir: unrecognized option"s + i + "\nTry 'rmdir --help' for more information.\033[0m";
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
            if (parent) {
                int size = path.size();
                std::string cd_message;
                for (int i = 0; i < size - 1; ++i) {
                    cd_count = 0;
                    for (int j = 0; j < size - i - 1; ++j) {
                        cd_message = cd()({path[j]}, {}, dir);
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
                    if (dir->find_file(path[size - i - 1]) != nullptr) {
                        return "\033[1;91mrmdir: failed to remove '" + path[size - i - 1] + "' Not a directory.\033[0m";
                    }
                    if (dir->find_dir(path[size - i - 1]) == nullptr) {
                        return "\033[1;91mrmdir: failed to remove '" + path[size - i - 1] + "' : No such file or directory.\033[0m";
                    } 
                    if (!(dir->find_dir(path[size - i - 1])->is_files_empty()) || !(dir->find_dir(path[size - i - 1])->is_directories_empty())) {
                        return "\033[1;91mrmdir: failed to remove '" + path[size - i - 1] + "' Directory not empty.\033[0m";
                    }
                    if (verbose) {
                        std::cout << "\033[1;97mrmdir: removing directory '" + path[size - i - 1] + "'\033[0m\n";
                    }
                    dir->removeSubDirectory(path[size - i - 1]);
                    while (cd_count-- != 0) {
                        cd()({"../"}, {}, dir);
                    }
                }
                if (dir->find_file(path[0]) != nullptr) {
                    return "\033[1;91mrmdir: failed to remove '" + path[0] + "' Not a directory.\033[0m";
                }
                if (dir->find_dir(path[0]) == nullptr) {
                    return "\033[1;91mrmdir: failed to remove '" + path[0] + "' : No such file or directory.\033[0m";
                } 
                if (!(dir->find_dir(path[0])->is_files_empty()) || !(dir->find_dir(path[0])->is_directories_empty())) {
                    return "\033[1;91mrmdir: failed to remove '" + path[0] + "' Directory not empty.\033[0m";
                }
                if (verbose) {
                    std::cout << "\033[1;97mrmdir: removing directory '" + path[0] + "'\033[0m\n";
                }
                dir->removeSubDirectory(path[0]);
            } else {
                for (int i = 0; i < path.size(); ++i) {
                    if (path[i] == ".") {
                        continue;
                    }
                    if (i == path.size() - 1) {
                        if (dir->find_file(path[i]) != nullptr) {
                            return "\033[1;91mrmdir: failed to remove '" + path[i] + "' Not a directory.\033[0m";
                        }
                        if (dir->find_dir(path[i]) == nullptr) {
                            return "\033[1;91mrmdir: failed to remove '" + path[i] + "' : No such file or directory.\033[0m";
                        } 
                        if (!(dir->find_dir(path[i])->is_files_empty()) || !(dir->find_dir(path[i])->is_directories_empty())) {
                            return "\033[1;91mrmdir: failed to remove '" + path[i] + "' Directory not empty.\033[0m";
                        }
                        if (verbose) {
                            std::cout << "\033[1;97mrmdir: removing directory '" + path[i] + "'\033[0m\n";
                        }
                        dir->removeSubDirectory(path[i]);
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
            return "\033[1;91mrmdir: missing operand.\nTry 'rmdir --help' for more information.\n\033[0m";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help") {
                return "\033[1;97m"s + 
                R"(
                    Usage: rmdir [OPTION]... DIRECTORY...
                    Remove the DIRECTORY(ies), if they are empty.

                    -p, --parents   remove DIRECTORY and its ancestors; e.g., 'rmdir -p a/b/c' is
                                        similar to 'rmdir a/b/c a/b a'
                    -v, --verbose   output a diagnostic for every directory processed
                        --help     display this help and exit
                        --version  output version information and exit

                )" + "\033[0m"s;
            }
            if (opts[0] == "--version") {
                return "\033[1;97mmkdir version 1.00\nWritten by Samvel Makaryan.\033[0m";
            }
            return "\033[1;91mrm: missing operand.\033[0m";
        
        }
    }
    return "";
}
