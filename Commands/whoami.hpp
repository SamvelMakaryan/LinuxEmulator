#ifndef WHOAMI_HPP_
#define WHOAMI_HPP_
#include <string>
#include "../src/System.hpp"
#include "Command.hpp"

class whoami : public Command {
public:
    whoami() = default;
    ~whoami() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //WHOAMI_HPP_
