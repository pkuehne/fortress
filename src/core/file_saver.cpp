#include "file_saver.h"
#include "yaml_converter.h"
#include <fstream>
#include <glog/logging.h>
#include <iostream>

void FileSaver::updateStatus(const std::string& status) {
    m_cb(++m_currentStep, m_totalSteps, status);
}

void FileSaver::saveState(const std::string& filename) {
    YAML::Node node;

    m_totalSteps += m_state->map()->getAreas().size();
    m_totalSteps += m_state->entityManager()->count();

    encodeMap(node);
    encodeAreaZero(node);
    std::ofstream fout(filename);
    fout << node;
}

void FileSaver::encodeMap(YAML::Node& node) {
    for (auto iter : m_state->map()->getAreas()) {
        node[iter.first] = iter.second;
        encodeArea(node, iter.first);
    }
}

void FileSaver::encodeAreaZero(YAML::Node& node) {
    // Catch ephemeral entities
    encodeArea(node, 0);
}

void FileSaver::encodeArea(YAML::Node& node, unsigned int area) {
    updateStatus(std::string("Saving Area " + std::to_string(area)));
    YAML::Node&& entityNode = node[area]["entities"];
    encodeEntities(entityNode, area);
}

void FileSaver::encodeEntities(YAML::Node& node, unsigned int area) {
    for (auto entity : m_state->entities(area)) {
        updateStatus(std::string("Saving Entity " + std::to_string(entity)));
        encodeEntity(m_state, node, entity);
    }
}
