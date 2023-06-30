#ifndef LS_HPP_
#define LS_HPP_
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "cd.hpp"

class ls : public Command {
public:
    ls() = default;
    ~ls() = default;
public:
    std::string operator()(const std::vector<std::string>&, const std::vector<std::string>&, Directory*&) override;
private:
    void print_dir(Directory&, std::function<bool(Directory*)>, bool) const;
    void print_file(Directory&, std::function<bool(File*)>, bool) const;
    void getPermission(std::string&, int) const;
};

#endif //LS_HPP_