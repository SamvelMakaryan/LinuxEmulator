#ifndef COMMAND_HPP_
#define COMMAND_HPP_
#include <vector>
#include <string>
#include "../Directory.hpp"

class Command {
public:
    Command() = default;
    virtual ~Command() = default;
public:
   virtual std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) = 0;
};

#endif //COMMAND_HPP_
