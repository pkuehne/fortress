#include "combat_component.h"
#include "dialog_component.h"
#include "key_component.h"
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
    save->locked = true;

    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->open, load->open);
    EXPECT_EQ(save->locked, load->locked);
}

TEST_F(SaveLoadTest, KeyComponent) {
    using T = KeyComponent;
    auto save = new T();

    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
}

TEST_F(SaveLoadTest, CombatComponent) {
    // Given
    using T = CombatComponent;
    auto save = new T();

    // When
    save->opponent = 123;

    // Then
    YAML::Node node;
    node = *save;

    auto load = new T();
    *load = node.as<T>();

    EXPECT_NE(save, load);
    EXPECT_EQ(save->opponent, load->opponent);
}