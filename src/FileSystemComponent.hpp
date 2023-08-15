#ifndef FILESYSTEMCOMPONENT_HPP_
#define FILESYSTEMCOMPONENT_HPP_
#include <string>
#include "User.hpp"
#include "Group.hpp"

class FileSystemComponent {
public:
    FileSystemComponent(const std::string&, const std::string&, const std::string&, int = Permission::none, int = Permission::none, int = Permission::none);
    FileSystemComponent(const FileSystemComponent&);
    FileSystemComponent(const FileSystemComponent&, const std::string&);
    FileSystemComponent(FileSystemComponent&&) noexcept = default;
    virtual ~FileSystemComponent() = default;
public:
    FileSystemComponent& operator=(const FileSystemComponent&) = default;
    FileSystemComponent& operator=(FileSystemComponent&&) noexcept = default;
public:
    virtual std::string getName() const;
    virtual void setName(const std::string&);
    virtual std::string getUserName() const;
    virtual void setUserName(const std::string&);
    virtual std::string getGroupName() const;
    virtual void setGroupName(const std::string&);
    virtual int getUserPermission() const;
    virtual int getGroupPermission() const;
    virtual int getOtherPermission() const;
    virtual void setUserPermission(int);
    virtual void setGroupPermission(int);
    virtual void setOtherPermission(int);
    virtual void addUserPermission(int);
    virtual void addGroupPermission(int);
    virtual void addOtherPermission(int);
    virtual void removeUserPermission(int);
    virtual void removeGroupPermission(int);
    virtual void removeOtherPermission(int);
protected:
    std::string m_name;
    int oth_permission;    
    User m_user;
    Group m_group;
};

#endif //FILESYSTEMCOMPONENT_HPP_

