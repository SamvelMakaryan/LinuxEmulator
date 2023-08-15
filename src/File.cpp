#include "File.hpp"

File::File(const std::string& name, const std::string& user, const std::string& group, int userPermission, int groupPermission, int otherPermission) 
: FileSystemComponent(name, user, group, userPermission, groupPermission, otherPermission),
  m_content() {}

File::File(const File& oth)
: File(oth, oth.m_name) {}

File::File(const File& oth, const std::string& name)
: FileSystemComponent(oth, name),
  m_content(oth.m_content) {}

std::string File::getContent() const {
    return m_content;
}

void File::setContent(const std::string& content) {
    m_content = content;
}
