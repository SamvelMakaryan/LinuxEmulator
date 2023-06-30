#ifndef CAT_HPP_
#define CAT_HPP_
#include <sstream>
#include <string>
#include "Command.hpp"
#include "cd.hpp"

class cat : public Command {
public:
    cat() = default;
    ~cat() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //CAT_HPP_