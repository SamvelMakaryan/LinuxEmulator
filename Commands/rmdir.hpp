#ifndef RMDIR_HPP_
#define RMDIR_HPP_
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "cd.hpp"

class rmdir : public Command {
public:
    rmdir() = default;
    ~rmdir() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //RMDIR_HPP_