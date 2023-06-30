#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_
#include <string>

namespace Permission {
    enum {
        none = 0,
        exexcute = 1,
        write = 2,
        read = 4
    };
}

class Component {
public:
    Component(const std::string&, int = Permission::none);
    Component(const Component&);
    Component(const Component&, const std::string&);
    Component(Component&&) noexcept = default;
    virtual ~Component() = default;
public:
    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) noexcept = default;
public:
    virtual std::string getName() const;
    virtual void setName(const std::string&);
    virtual void setPermission(int);
    virtual int getPermission() const;
    virtual void addPermission(int);
    virtual void removePermission(int);
protected:
    std::string m_name;
    int m_permission;
};

#endif //COMPONENT_HPP_