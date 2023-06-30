#include "TxtFile.hpp"

TxtFile::TxtFile(const std::string& name, const std::string& user, const std::string& group, int userPermission, int groupPermission, int otherPermission)
: File(name, user, group, userPermission, groupPermission, otherPermission) {}

TxtFile::TxtFile(const TxtFile& oth)
: TxtFile(oth, oth.m_name) {}

TxtFile::TxtFile(const TxtFile& oth, const std::string& name)
: File(oth, name) {}

void TxtFile::read() {
    std::cout << m_content << "\n";
}