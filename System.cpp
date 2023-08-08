#include "System.hpp"

System::System()
 : m_history {}
{
    m_commands.insert(std::make_pair("mkdir", new mkdir));
    m_commands.insert(std::make_pair("ls", new ls));
    m_commands.insert(std::make_pair("cd", new cd));
    m_commands.insert(std::make_pair("touch", new touch));
    m_commands.insert(std::make_pair("pwd", new pwd));
    m_commands.insert(std::make_pair("rmdir", new rmdir));
    m_commands.insert(std::make_pair("rm", new rm));
    m_commands.insert(std::make_pair("date", new date));
    m_commands.insert(std::make_pair("cal", new cal));
    m_commands.insert(std::make_pair("chmod", new chmod));
    m_commands.insert(std::make_pair("history", new history));
    m_commands.insert(std::make_pair("cat", new cat));
    m_commands.insert(std::make_pair("useradd", new useradd));
    m_commands.insert(std::make_pair("userdel", new userdel));
    m_commands.insert(std::make_pair("su", new su));
    m_commands.insert(std::make_pair("whoami", new whoami));
    createTree();
}

System::~System() {
    for (auto& i : m_commands) {
        delete i.second;
    }
}

void System::execute(const std::string& input) {
    std::stringstream ss(input);
    std::string command;
    ss >> command;
    if (command == "exit") {
        exit(0);
    }
    m_history += input + "\n";
    auto it = m_commands.find(command);
    if (it == m_commands.end()) {
        std::cerr << "\033[1;91m" << command << ": command not found.\033[0m\n";
        return;
    }
    std::vector<std::string> args;
    std::vector<std::string> opts;
    std::string argument;
    while (ss >> argument) {
        if (argument[0] == '-') {
            opts.push_back(argument);
        } else {
            args.push_back(argument);
        }
    }
    std::string return_message;
    if (command == "history") {
        try {
            return_message = (*m_commands["history"])({m_history}, {opts}, m_current);
        } catch (char const* s) {
            m_history.clear();
            return;
        }
        std::cout << return_message;
        return;
    }
    return_message = (*it->second)(args, opts, m_current);
    if (!return_message.empty()) {
        std::cout << return_message << "\n";
    }
}

void System::createTree() {
    mkdir make_dir;
    make_dir({"boot", "dev", "home", "etc", "bin", "sys", "usr", "var"}, {}, m_current);
    cd change_dir;
    make_dir({"home/user"}, {}, m_current);
    make_dir({"home/root"}, {}, m_current);
    change_dir({"home/user"}, {}, m_current);
}

Directory* System::getCurrentDirectory() const {
    return m_current;
}

std::string System::getCurrentPath() const {
    return pwd()({},{}, m_current);
}

User* System::getCurrentUser() {
    return m_current_user;
}

std::vector<User> System::getAllUsers() {
    return m_users;
}

void System::addUser(const std::string& name) {
    m_users.push_back(User(name));
}

std::string System::removeUser(const std::string& name) {
    for (auto i = m_users.begin(); i != m_users.end(); ++i) {
        if (i->getName() == name) {
            m_users.erase(i);
            return "";
        }
    }
    return "\033[1;91muserdel: user" + name + "does not exist\033[0m";
}

User* System::FindUser(const std::string& name) {
    for (auto& i : m_users) {
        if (i.getName() == name) {
            return &i;
        }
    }
    return nullptr;
}

void System::setCurrentUser(User* user) {
    m_current_user = user;
}
