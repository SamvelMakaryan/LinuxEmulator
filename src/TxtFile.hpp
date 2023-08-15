#ifndef TXTFILE_HPP_
#define TXTFILE_HPP_
#include <iostream>
#include "File.hpp"

class TxtFile : public File {
public:
    TxtFile(const std::string&, const std::string&, const std::string&, int = Permission::none, int = Permission::none, int = Permission::none);
    TxtFile(const TxtFile&);
    TxtFile(const TxtFile&, const std::string&);
    virtual ~TxtFile() = default;
public:
    void read() override;
};

#endif //TXTFILE_HPP_