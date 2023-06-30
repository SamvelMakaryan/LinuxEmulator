#include "FileSystemComponent.hpp"

FileSystemComponent::FileSystemComponent(const std::string& name, const std::string& user, const std::string& group, int userPermission, int groupPermission, int otherPermission) 
: m_name(name),
  oth_permission(otherPermission),
  m_user(user, userPermission),
  m_group(group, groupPermission) {}

FileSystemComponent::FileSystemComponent(const FileSystemComponent& oth)
: FileSystemComponent(oth, oth.m_name) {}

FileSystemComponent::FileSystemComponent(const FileSystemComponent& oth, const std::string& name)
: m_name(name),
  m_user(oth.m_user),
  m_group(oth.m_group),
  oth_permission(oth.oth_permission) {}

std::string FileSystemComponent::getName() const {
    return m_name;
}

void FileSystemComponent::setName(const std::string& name) {
    m_name = name;
}

std::string FileSystemComponent::getUserName() const {
    return m_user.getName();
}

void FileSystemComponent::setUserName(const std::string& name) {
    m_user.setName(name);
}

std::string FileSystemComponent::getGroupName() const {
    return m_group.getName();
}

void FileSystemComponent::setGroupName(const std::string& name) {
    m_group.setName(name);
}

int FileSystemComponent::getUserPermission() const {
    return m_user.getPermission();
}

int FileSystemComponent::getGroupPermission() const {
    return m_group.getPermission();
}

int FileSystemComponent::getOtherPermission() const {
    return oth_permission;
}

void FileSystemComponent::addUserPermission(int permission) {
    m_user.addPermission(permission);
}

void FileSystemComponent::addGroupPermission(int permission) {
    m_group.addPermission(permission);
}

void FileSystemComponent::addOtherPermission(int permission) {
    oth_permission |= permission;
}

void FileSystemComponent::removeUserPermission(int permission) {
    m_user.removePermission(permission);
}

void FileSystemComponent::removeGroupPermission(int permission) {
    m_group.removePermission(permission);
}

void FileSystemComponent::removeOtherPermission(int permission) {
    if (oth_permission & permission != 0) {
        oth_permission &= ~permission;
    }
}

void FileSystemComponent::setUserPermission(int permission) {
    m_user.setPermission(permission);
}

void FileSystemComponent::setGroupPermission(int permission) {
    m_group.setPermission(permission);
}

void FileSystemComponent::setOtherPermission(int permission) {
    oth_permission = permission;
}