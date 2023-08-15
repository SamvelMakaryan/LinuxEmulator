#include "User.hpp"

User::User(const std::string& name, int permission)
: Component(name, permission) {}

User::User(const User& oth)
: User(oth, oth.m_name) {}

User::User(const User& oth, const std::string& name)
: Component(oth, name) {}

