#include "date.hpp"

std::string date::operator()(const std::vector<std::string>& args, const std::vector<std::string>& opts, Directory*& dir)  {
    using namespace std::string_literals;
    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", local_time);
    return "\033[1;97m"s + buffer + "\033[0m";
}