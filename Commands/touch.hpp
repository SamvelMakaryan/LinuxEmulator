#ifndef TOUCH_HPP_
#define TOUCH_HPP_
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "../src/TxtFile.hpp"
#include "../src/System.hpp"
#include "cd.hpp"

class touch : public Command {
public:
    touch() = default;
    ~touch() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};
#endif //TOUCH_HPP_
