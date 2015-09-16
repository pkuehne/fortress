#include "file_loader.h"
#include <fstream>
#include <iostream>

void FileLoader::loadState ()
{
    std::cout << "Loading...";
    std::ifstream l_file ("World1.sav");
    if (!l_file.is_open()) {
        std::cout << "Failed!" << std::endl;
        return;
    }

    while (!l_file.eof()) {
        std::string l_line;
        std::getline (l_file, l_line);
        m_lines.push_back (l_line);
    }
    std::cout << "Done" << std::endl;

    for (std::string& l_line : m_lines) {
        
    }
}
