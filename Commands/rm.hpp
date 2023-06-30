#ifndef RM_HPP_
#define RM_HPP_
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "cd.hpp"

class rm : public Command {
public:
    rm() = default;
    ~rm() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //RM_HPP_

