#include <limits.h>
#include "gtest/gtest.h"
#include "logging/hpy_logging.h"

class LoggingTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
};

TEST_F(LoggingTest, GetCurrentTime_ShouldPass)
{
    ASSERT_NE("", Logging::GetCurrentTime());
}

TEST_F(LoggingTest, Simple_ShouldPass)
{
    ASSERT_EQ(true, LOG.Info("hehe"));
}

