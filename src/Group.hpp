#ifndef GROUP_HPP_
#define GROUP_HPP_
#include <string>
#include "Component.hpp"

class Group : public Component {
public:
    Group(const std::string&, int = Permission::none);
    Group(const Group&);
    Group(const Group&, const std::string&);
    ~Group() = default;
};

#endif //GROUP_HPP_