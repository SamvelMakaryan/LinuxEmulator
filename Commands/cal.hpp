#ifndef CAL_HPP_
#define CAL_HPP_
#include <iomanip>
#include <string>
#include <ctime>
#include "Command.hpp"

class cal : public Command {
public:
    cal() = default;
    ~cal() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //CAL_HPP_
