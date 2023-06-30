#include "cat.hpp"

std::string cat::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {
        if (opts.size() > 1) {
            return "\033[1;91mcat: invalid optons for cat without operands.\033[0m";
        }
        bool numbers = false;
        bool blocks = false;
        if (opts.size() == 1) {
            if (opts[0] == "-n" || opts[0] == "--number") {
                numbers = true;
            } else if (opts[0] == "-b" || opts[0] == "--number-nonblank") {
                blocks = true;
            } else {
                return "\033[1;91mrm: unrecognized option"s + opts[0] + "\nTry 'cat --help' for more information.\033[0m";
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
            for (int i = 0; i < path.size(); ++i) {
                if (i == path.size() - 1) {
                    if (dir->find_dir(path[i]) != nullptr) {
                        return "\033[1;91mcat: '" + path[i] + "' Is a directory.\033[0m";
                    } 
                    File* file = dir->find_file(path[i]);
                    if (file == nullptr) {
                        return "\033[1;91mcat: '" + path[i]  + "'No such file or directory.\033[0m";
                    }
                    std::stringstream lines(file->getContent());
                    std::string current_line;
                    int lines_count = 0;
                    if (numbers) {
                        while (std::getline(lines, current_line)) {
                            std::cout << "\033[1;97m" << lines_count++ << current_line << "\033[0m\n";
                        }
                    } else if (blocks) {
                        while (std::getline(lines, current_line)) {
                            if (!current_line.empty()) {
                                std::cout << "\033[1;97m" << lines_count++ << current_line << "\033[0m\n";
                            }
                        }
                    } else {
                        file->read();
                    }
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
        }
    } else {
        if (opts.empty()) {
            return "\033[1;91mrm: missing operand.\nTry 'cat --help' for more information.\033[0m";
        }
        if (opts.size() == 1) {
            if (opts[0] == "--help") {
                return "\033[1;97m"s +
                R"(
                    Usage: cat [OPTION]... [FILE]...
                    Concatenate FILE(s) to standard output.

                    -b, --number-nonblank    number nonempty output lines, overrides -n
                    -n, --number             number all output lines
                        --help     display this help and exit
                        --version  output version information and exit

                )" + "\033[0m"s;
            } else if (opts[0] == "--version") {
                return "\033[1;97mcat version 1.00\nWritten by Samvel Makaryan.\033[0m";
            }
            return "\033[1;91mcat: missing operand.\033[0m";
        }
        return "\033[1;91mcat: invalid optons for cat without operands.\033[0m";
    }
    return "";
}
