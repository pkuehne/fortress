#include <config_manager.h>
#include <fstream>
#include <iostream>

Tag ConfigManager::getTag (const std::string& tag)
{
    return m_tags[tag];
}

void ConfigManager::readFile (const std::string& config)
{
    std::string l_line;
    std::ifstream l_file (config.c_str());
    if (!l_file.is_open()) throw std::runtime_error(std::string("Could not open config file: ") + config);

    do {
        getline (l_file, l_line);
        std::string tag, value;

        // Check for comments
        if (l_line[0] == '#') continue;

        Tag l_tag (l_line);
        m_tags[l_tag.getName()] = l_tag;
    } while (l_line.size() > 0);
}
