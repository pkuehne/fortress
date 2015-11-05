#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <map>
#include <string>
#include "tag.h"

class ConfigManager {
public:
    Tag getTag (const std::string& tag);
    void readFile (const std::string& config);
private:
    std::map<std::string, Tag> m_tags;
};

#endif
