#include <config_manager.h>
#include <gtest/gtest.h>

TEST (ConfigManager, ReadTagsFromFile)
{
    ConfigManager l_manager;
    l_manager.readFile ("test.cfg");
    EXPECT_EQ ("TestVal", l_manager.getTag("TestTag").str);
}

TEST (ConfigManager, TagsAreConverted)
{
    ConfigManager l_manager;
    l_manager.readFile ("test.cfg");
    EXPECT_EQ ("Hello World!", l_manager.getTag("String").str);
    EXPECT_EQ (100, l_manager.getTag("Number").num);
    EXPECT_FLOAT_EQ (123.456, l_manager.getTag("Decimal").dec);
}

TEST (ConfigManager, HashIsComment)
{
    ConfigManager l_manager;
    l_manager.readFile ("test.cfg");
    EXPECT_EQ ("Comment2", l_manager.getTag("Comment").str);
    EXPECT_EQ ("", l_manager.getTag("Comment2").str);
}
