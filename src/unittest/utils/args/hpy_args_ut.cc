#include <limits.h>
#include "gtest/gtest.h"
#include "utils/args/hpy_args.h"

class ArgsTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    Args args;
    Options option;
};

TEST_F(ArgsTest, DoesnotHave_ShouldPass)
{
    ASSERT_EQ(false, args.HasKey(Options::RUN_AS_CLINET));
}

TEST_F(ArgsTest, HasClient_ShouldPass)
{
    ASSERT_EQ(true, option.DoesHaveKey(Options::RUN_AS_CLINET));
}


