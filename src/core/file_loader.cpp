#include "file_loader.h"
#include "area_info.h"
#include "yaml_converter.h"
#include <fstream>
#include <iostream>

void FileLoader::updateStatus(const std::string& status) {
    m_cb(++m_currentStep, m_totalSteps, status);
}

void FileLoader::loadState(const std::string& filename) {
    m_cb(m_currentStep, m_totalSteps, "Parsing file...");

    YAML::Node node = YAML::LoadFile(filename);

    m_totalSteps += node.size();

    for (unsigned int ii = 0; ii < node.size(); ii++) {
        updateStatus(std::string("Loading Area " + std::to_string(ii)));
        if (ii) {
            AreaInfo area = node[ii].as<AreaInfo>();
            m_map->addArea(area, ii);
        }
        YAML::Node&& entityNode = node[ii]["entities"];
        decodeEntities(entityNode);
    }
}

void FileLoader::decodeEntities(const YAML::Node& node) {
    for (YAML::const_iterator iter = node.begin(); iter != node.end(); ++iter) {
        m_yaml.decodeEntity(iter->second, iter->first.as<EntityId>());
    }
}