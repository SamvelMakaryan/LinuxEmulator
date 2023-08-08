#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include "Directory.hpp"
#include "Commands.hpp"
#include "User.hpp"

class System {
public:
    System();
    ~System();
public:
    void execute(const std::string&);
    Directory* getCurrentDirectory() const;
    std::string getCurrentPath() const;
    static User* getCurrentUser();
    static void setCurrentUser(User*);
    static std::vector<User> getAllUsers();
    static void addUser(const std::string&);
    static std::string removeUser(const std::string&);
    static User* FindUser(const std::string&);
private:
    void createTree();
private:
    static inline Directory m_root {"/", "root", "root", nullptr, Permission::read | Permission::exexcute, Permission::read, Permission::none};
    static inline Directory* m_current {&m_root};
    std::string m_history;
    static inline std::vector<User> m_users {User("root"), User("user")};
    static inline User* m_current_user {&m_users[1]};
    std::unordered_map<std::string, Command*> m_commands;
};

#endif //SYSTEM_HPP_
