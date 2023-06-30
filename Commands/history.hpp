#ifndef HISTORY_HPP_
#define HISTORY_HPP_
#include <string>
#include "Command.hpp"

class history : public Command {
public:
    history() = default;
    ~history() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //HISTORY_HPP_