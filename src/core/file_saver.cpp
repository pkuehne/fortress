#include "file_saver.h"
#include "game_engine.h"
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

    std::ofstream fout(filename);
    fout << node;
}

void FileSaver::encodeMap(YAML::Node& node) {

    MapManager* map = m_state->map();
    for (auto iter : map->getAreas()) {
        updateStatus(std::string("Saving Area " + std::to_string(iter.first)));
        node[iter.first] = iter.second;
        encodeEntities(node, iter.first);
    }
}

void FileSaver::encodeEntities(YAML::Node& node, unsigned int area) {
    EntityManager* entities = m_state->entityManager();
    for (auto entity : entities->get(area)) {
        updateStatus(std::string("Saving Entity " + std::to_string(entity)));
        encodeEntity(m_state, node, entity);
    }
}