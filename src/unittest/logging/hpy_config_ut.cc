#include <limits.h>
#include "gtest/gtest.h"
#include "logging/hpy_config.h"
#include "logging/hpy_const.h"

class ConfigTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        config.Init("logging/hpy_logging.ini");
    }
    virtual void TearDown() {
        ;
    }
    Config config;
};

TEST_F(ConfigTest, IsHave_ShouldPass)
{
    ASSERT_EQ(true, config.IsHave(hpy::Config::kLogFilePath));
}

TEST_F(ConfigTest, GetValue_ShouldPass)
{
    ASSERT_EQ("../logs/log.txt", config.GetValue(hpy::Config::kLogFilePath));
}


