#include "dialog_component.h"
#include "openable_component.h"
#include "player_component.h"
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

class SaveLoadTest : public ::testing::Test {};

TEST_F(SaveLoadTest, PlayerComponent) {
    using T = PlayerComponent;
    auto save = new T();
    save->turn = 12345;
    save->playerTurn = true;

    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->turn, load->turn);
    EXPECT_EQ(save->playerTurn, load->playerTurn);
}

TEST_F(SaveLoadTest, DialogComponent) {
    using T = DialogComponent;
    auto save = new T();
    save->inConversationWith = 12345;
    save->dialogOptions.push_back("Test option");
    save->dialogText = "Foobar";

    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->inConversationWith, load->inConversationWith);
    EXPECT_EQ(save->dialogOptions, load->dialogOptions);
    EXPECT_EQ(save->dialogText, load->dialogText);
}

TEST_F(SaveLoadTest, OpenableComponent) {
    using T = OpenableComponent;
    auto save = new T();
    save->open = true;

    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->open, load->open);
}