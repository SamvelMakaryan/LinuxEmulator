#ifndef USERDEL_HPP_
#define USERDEL_HPP_
#include "../System.hpp"
#include "Command.hpp"

class userdel : public Command {
public:
    userdel() = default;
    ~userdel() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //USERDEL_HPP_