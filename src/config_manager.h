#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <map>
#include <string>

typedef struct {
    std::string str;
    long        num;
    double      dec;
} TagValue;

class ConfigManager {
public:
    void setTag (const std::string& tag, const TagValue& val);
    TagValue getTag (const std::string& tag);
    void readFile (const std::string& config);
    void stringToTagValue (const std::string& input, TagValue& output);
private:
    std::map<std::string, TagValue> m_tags;
};

#endif
