#ifndef MKDIR_HPP_
#define MKDIR_HPP_
#include <sstream>
#include <vector>
#include <string>
#include "Command.hpp"
#include "cd.hpp"
#include "../src/System.hpp"

class mkdir : public Command {
public:
    mkdir() = default;
    ~mkdir() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //MKDIR_HPP_
