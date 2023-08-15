#ifndef DIRECTORY_HPP_
#define DIRECTORY_HPP_
#include <iostream>
#include <string>
#include <set>
#include "FileSystemComponent.hpp"
#include "File.hpp"

class Directory : public FileSystemComponent {
public:
    Directory(const std::string&, const std::string&, const std::string&, Directory* = nullptr, int = Permission::none, int = Permission::none, int = Permission::none);
    Directory(const Directory&);
    Directory(const Directory&, const std::string&);
    ~Directory() = default;
public:
    Directory* getParent() const;
    std::set<File*> getFiles() const;
    std::set<Directory*> getDirectories() const;
    void setParent(Directory*);
    void addFile(File&);
    void removeFile(const std::string&);
    void addSubDirectory(Directory&);
    void removeSubDirectory(const std::string&);
    Directory* find_dir(const std::string&);
    File* find_file(const std::string&);
    bool is_files_empty() const;
    bool is_directories_empty() const;
    void clear_files();
    void clear_dirs();
    void clear();
private:
    std::set<File*> m_files;
    std::set<Directory*> m_subdirectoies;
    Directory* m_parent;    
};

#endif //DIRECTORY_HPP_