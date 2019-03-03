#include "dialog_component.h"
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

    auto load = new PlayerComponent();
    *load = node.as<PlayerComponent>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->turn, load->turn);
    EXPECT_EQ(save->playerTurn, load->playerTurn);
}

TEST_F(SaveLoadTest, DialogComponent) {
    auto save = new DialogComponent();
    save->inConversationWith = 12345;
    save->dialogOptions.push_back("Test option");
    save->dialogText = "Foobar";

    YAML::Node node;
    node = *save;

    auto load = new DialogComponent();
    *load = node.as<DialogComponent>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->inConversationWith, load->inConversationWith);
    EXPECT_EQ(save->dialogOptions, load->dialogOptions);
    EXPECT_EQ(save->dialogText, load->dialogText);
}