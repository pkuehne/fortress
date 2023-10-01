#include "file_saver.h"
#include "entity_manager.h"
#include "map_manager.h"
#include "yaml_converter.h"
#include <fstream>
#include <iostream>

void FileSaver::updateStatus(const std::string& status) {
    m_cb(++m_currentStep, m_totalSteps, status);
}

void FileSaver::saveState(const std::string& filename) {
    YAML::Node node;

    m_totalSteps += m_map->getAreas().size();
    m_totalSteps += m_entities->count();

    encodeMap(node);
    std::ofstream fout(filename);
    fout << node;
}

void FileSaver::encodeMap(YAML::Node& node) {
    for (auto iter : m_map->getAreas()) {
        node[iter.first] = iter.second;
        // encodeArea(node, iter.first);
    }
    // encodeArea(node, 0);
}

void FileSaver::encodeArea(YAML::Node& node, unsigned int area) {
    updateStatus(std::string("Saving Area " + std::to_string(area)));
    // YAML::Node&& entityNode = node[area]["entities"];
    // encodeEntities(entityNode, area);
}

void FileSaver::encodeEntities(YAML::Node& node, unsigned int area) {
    for (auto entity : m_entities->get(area)) {
        updateStatus(std::string("Saving Entity " + std::to_string(entity)));
    }
}
