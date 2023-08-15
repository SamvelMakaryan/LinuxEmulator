#include "Component.hpp"

Component::Component(const std::string& name, int permission) 
: m_name(name),
  m_permission(permission) {}

Component::Component(const Component& oth)
: Component(oth, oth.m_name) {}

Component::Component(const Component& oth, const std::string& name)
: m_name(name),
  m_permission(oth.m_permission) {}

std::string Component::getName() const {
    return m_name;
}

int Component::getPermission() const {
    return m_permission;
}

void Component::setPermission(int permission) {
    m_permission = permission;
}

void Component::setName(const std::string& name) {
    m_name = name;
}

void Component::addPermission(int permission) {
    m_permission |= permission;
}

void Component::removePermission(int permission) {
    if (m_permission & permission != 0) {
        m_permission &= ~permission;
    }
}
