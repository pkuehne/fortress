#include "file_loader.h"
#include "area_info.h"
#include "yaml_converter.h"
#include <fstream>
#include <glog/logging.h>
#include <iostream>

void FileLoader::updateStatus(const std::string& status) {
    m_cb(++m_currentStep, m_totalSteps, status);
}

void FileLoader::loadState(const std::string& filename) {
    YAML::Node node = YAML::LoadFile(filename);
    for (unsigned int ii = 1; ii < node.size(); ii++) {
        std::cout << "Area = " << ii << std::endl;
        AreaInfo area = node[ii].as<AreaInfo>();
        m_state->map()->addArea(area, ii);
    }
}
