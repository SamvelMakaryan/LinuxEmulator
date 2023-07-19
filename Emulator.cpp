#include <iostream>
#include <string>

#include "System.hpp"
#include "File.hpp"
#include "TxtFile.hpp"
#include "Directory.hpp"
#include "Opening.hpp"

int main() {
    System sys;
    std::string input;
	opening();
    while (true) {
        std::cout << "\033[1;92m" << System::getCurrentUser()->getName() << "@hp:" << "\033[1;94m" << sys.getCurrentPath() << "\033[95m$ "; 
        std::getline(std::cin, input);
        sys.execute(input);
    }   
}
