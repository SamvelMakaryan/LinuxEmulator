#ifndef CD_HPP_
#define CD_HPP_
#include <sstream>
#include <string>
#include <vector>
#include "../System.hpp"
#include "Command.hpp"

class cd : public Command {
public:
    cd();
    ~cd() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
private:
    Directory* last_directory;
};

#endif //CD_HPP_