#ifndef SU_HPP_
#define SU_HPP_
#include <string>
#include "../src/System.hpp"
#include "Command.hpp"

class su : public Command {
public:
    su() = default;
    ~su() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //SU_HPP_
