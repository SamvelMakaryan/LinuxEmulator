#ifndef DATE_HPP_
#define DATE_HPP_
#include <string>
#include <ctime>
#include "Command.hpp"

class date : public Command {
public: 
    date() = default;
    ~date() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
};

#endif //DATE_HPP_