#include "file_loader.h"
#include "tag.h"
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


    for (unsigned int ii = 0; ii < m_lines.size(); ii++) {
        Tag l_tag (m_lines[ii]);
        if (l_tag.getName() == "ENTITY") {
            // Set up the entity
            EntityId id = l_tag.getNum();
            Location location = loadLocation (ii+1);
            ii+=3;
            m_engine->getEntities()->addEntity (id, location);
            std::cout << id << ": ("<< location.x << ","<< location.y << "," << location.z << ")" << std::endl;
        }
    }
}


Location FileLoader::loadLocation (unsigned int pos){
    Location location;
    for (unsigned int ii = 0; ii < 3; ii++) {
        Tag l_tag (m_lines[pos+ii]);
        if (l_tag.getName() == "LOCATION_X") location.x = l_tag.getNum();
        if (l_tag.getName() == "LOCATION_Y") location.y = l_tag.getNum();
        if (l_tag.getName() == "LOCATION_Z") location.z = l_tag.getNum();
    }
    return location;
}
