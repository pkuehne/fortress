#include <config_manager.h>
#include <fstream>
#include <iostream>
#include <sstream>

void ConfigManager::setTag (const std::string& tag, const TagValue& value)
{
    m_tags[tag] = value;
}

TagValue ConfigManager::getTag (const std::string& tag)
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

        size_t tagStart = l_line.find("[");
        size_t valStart = l_line.find(":");
        size_t tagEnd   = l_line.find("]");
        if (tagStart == std::string::npos ||
            valStart == std::string::npos ||
            tagEnd   == std::string::npos) {
                continue; // Not a valid [tag:value] pair
        }
        tag.assign (l_line.substr(tagStart+1, valStart-tagStart-1));
        value.assign (l_line.substr(valStart+1, tagEnd-valStart-1));

        TagValue l_tagValue;
        stringToTagValue (value, l_tagValue);
        setTag (tag, l_tagValue);
    } while (l_line.size() > 0);
}

void ConfigManager::stringToTagValue (const std::string& input, TagValue& output)
{
    std::string::size_type l_size;
    output.str = input;
    try {
        output.num = std::stol (input);
    } catch (std::exception& e) {
        output.num = 0;
    }
    try {
        output.dec = std::stod (input);
    } catch (std::exception& e) {
        output.dec = 0.0;
    }

}
