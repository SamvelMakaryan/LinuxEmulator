#ifndef PWD_HPP_
#define PWD_HPP_
#include <string>
#include "Command.hpp"
#include "cd.hpp"

class pwd : public Command {
public:
    pwd() = default;
    ~pwd() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //PWD_HPP_