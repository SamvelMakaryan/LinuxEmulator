#ifndef FILE_HPP_
#define FILE_HPP_
#include <string>
#include "FileSystemComponent.hpp"

class File : public FileSystemComponent {
public:
    File(const std::string&, const std::string&, const std::string&, int = Permission::none, int = Permission::none, int = Permission::none);
    File(const File&);
    File(const File&, const std::string&);
    virtual ~File() = default;
public:
    virtual std::string getContent() const;
    virtual void setContent(const std::string&);
    virtual void read() = 0;
protected:
    std::string m_content;
};

#endif //FILE_HPP_