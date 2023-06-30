#include "Directory.hpp"

Directory::Directory(const std::string& name, const std::string& user, const std::string& group, Directory* parent, int userPermmission, int groupPermmission, int otherPermmission)
: FileSystemComponent(name, user, group, userPermmission, groupPermmission, otherPermmission),
  m_files(),
  m_subdirectoies(),
  m_parent(parent) {}

Directory::Directory(const Directory& oth)
: Directory(oth, oth.m_name) {}

Directory::Directory(const Directory& oth, const std::string& name)
: FileSystemComponent(oth, name),
  m_files(oth.m_files),
  m_subdirectoies(oth.m_subdirectoies),
  m_parent(m_parent) {}

Directory* Directory::getParent() const {
    return m_parent;
}

std::set<File*> Directory::getFiles() const {
    return m_files;
}

std::set<Directory*> Directory::getDirectories() const {
    return m_subdirectoies;
}

void Directory::setParent(Directory* parent) {
    m_parent = parent;
}

void Directory::addFile(File& file) {
    m_files.insert(&file);
}

void Directory::removeFile(const std::string& name) {
    for (auto& i : m_files) {
        if (name == i->getName()) {
            auto it = i;
            m_files.erase(i);
            delete it;
            return;
        }
    }
}

void Directory::addSubDirectory(Directory& dir) {
    m_subdirectoies.insert(&dir);
}

void Directory::removeSubDirectory(const std::string& name) {
    // std::clog <<  "-" << getName() << "-"  <<std::endl;
    for (auto& i : m_subdirectoies) {
        if (name == i->getName()) {
            // std::clog << i->getName() << std::endl;
            // m_subdirectoies.erase(i);
            return;
        }
    }
}

Directory* Directory::find_dir(const std::string& name) {
    for (auto& i : m_subdirectoies) {
        if (i->getName() == name) {
            return i;
        }
    }
    return nullptr;
}

File* Directory::find_file(const std::string& name) {
    for (auto& i : m_files) {
        if (i->getName() == name) {
            return i;
        }
    }
    return nullptr;
}

bool Directory::is_files_empty() const {
    return m_files.empty();
}

bool Directory::is_directories_empty() const {
    return m_subdirectoies.empty();
}

void Directory::clear_files() {
    for (auto& i : m_files) {
        removeFile(i->getName());
    }
}

void Directory::clear_dirs() {
    for (auto& i : m_subdirectoies) {
        i->clear_dirs();
        removeSubDirectory(i->getName());
    }
}

void Directory::clear() {
    clear_files();
    clear_dirs();
}
