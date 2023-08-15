#ifndef USERADD_HPP_
#define USERADD_HPP_
#include "../src/System.hpp"
#include "Command.hpp"
#include "cd.hpp"
#include "mkdir.hpp"

class useradd : public Command {
public:
    useradd() = default;
    ~useradd() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //USERADD_HPP_
