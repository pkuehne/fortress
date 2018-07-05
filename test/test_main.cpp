#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glog/logging.h>
#include <game_engine.h>

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    ::testing::InitGoogleMock (&argc, argv);
    ::google::InitGoogleLogging (argv[0]);
    
    return RUN_ALL_TESTS();
}
