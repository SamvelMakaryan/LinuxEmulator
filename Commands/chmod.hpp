#ifndef CHMOD_HPP_
#define CHMOD_HPP_
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "cd.hpp"

class chmod : public Command {
public: 
    chmod() = default;
    ~chmod() = default;
    
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
private:
};

#endif //CHMOD_HPP_