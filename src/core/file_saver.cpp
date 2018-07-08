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
    unsigned int height = map->getMapHeight();
    unsigned int width = map->getMapWidth();
    unsigned int depth = map->getMapDepth();

    for (unsigned int d = 0; d < depth; d++) {
        for (unsigned int h = 0; h < height; h++) {
            for (unsigned int w = 0; w < width; w++) {
                Location loc(w, h, d, 0);
                const Tile& tile = map->getTile(loc);
                node.push_back(tile);
            }
        }
    }
}

// void FileSaver::saveState() {

// }
