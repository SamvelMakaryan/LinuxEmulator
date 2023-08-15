#ifndef USER_HPP_
#define USER_HPP_
#include <string>
#include "Component.hpp"

class User : public Component {
public:
    User(const std::string&, int = Permission::none);
    User(const User&);
    User(const User&, const std::string&);
    ~User() = default;
};

#endif //USER_HPP_