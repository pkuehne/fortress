#include "player_component.h"
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

class SaveLoadTest : public ::testing::Test {};

TEST_F(SaveLoadTest, PlayerComponent) {
    auto save = new PlayerComponent();
    save->turn = 12345;
    save->playerTurn = true;

    YAML::Node node;
    node = *save;

    EXPECT_EQ(save->turn, node["turn"].as<unsigned int>());

    auto load = new PlayerComponent();
    *load = node.as<PlayerComponent>();

    EXPECT_EQ(save->turn, load->turn);
    EXPECT_EQ(save->playerTurn, load->playerTurn);
}