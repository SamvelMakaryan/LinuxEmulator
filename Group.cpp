#include "Group.hpp"

Group::Group(const std::string& name, int permission)
: Component(name, permission) {}

Group::Group(const Group& oth)
: Group(oth, oth.m_name) {}

Group::Group(const Group& oth, const std::string& name)
: Component(oth, name) {}
