#include "file_saver.h"
#include "game_engine.h"
#include "yaml_converter.h"
#include <fstream>
#include <glog/logging.h>
#include <iostream>
#include <typeinfo>

void FileSaver::saveState(const std::string& filename) {
    YAML::Node node;
    encodeMap(node);

    std::ofstream fout(filename);
    fout << node;
}

void FileSaver::encodeMap(YAML::Node& node) {

    MapManager* map = m_state->map();
    for (auto iter : map->getAreas()) {
        node[iter.first] = iter.second;
    }
}

void FileSaver::encodeArea(YAML::Node& node, unsigned int area) {}

// void FileSaver::saveState() {

// }
