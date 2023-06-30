#include "touch.hpp"

std::string touch::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir) {
    using namespace std::string_literals;
    if (!args.empty()) {
        for (auto& i : args) {
            std::stringstream ss(i);
            std::vector<std::string> path;
            std::string cur;
            while (std::getline(ss, cur, '/')) {
                path.push_back(cur);
            }
            int cd_count = 0;
            for (int i = 0; i < path.size(); ++i) {
                if (path[i] == ".") {
                    continue;
                }
                if (i == path.size() - 1) {
                    if (!(dir->find_dir(path[i]) != nullptr || dir->find_file(path[i]) != nullptr)) {
                        dir->addFile(*new TxtFile(path[i], System::getCurrentUser()->getName(), dir->getGroupName(), Permission::read | Permission::write | Permission::exexcute, Permission::read | Permission::exexcute, Permission::read));
                    }
                    continue;
                } else {
                    std::string cd_message = cd()({path[i]}, {}, dir);
                    if (cd_message != "") {
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
    } else {
        if (opts.empty()) {
            return "\033[1;91mtouch: missing file operand\nTry 'touch --help' for more information.\033[0m";
        }
        if (opts.size() > 1) {
            return "\033[1;91mtouch: this version doesn't support options besides --help, --version.\033[0m";
        }
        if (opts[0] == "--help") {
            return "\033[1;91"s +
            R"(
                Usage: touch [OPTION]... FILE...
                A FILE argument that does not exist is created empty.

                This version doesn't support options.

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
