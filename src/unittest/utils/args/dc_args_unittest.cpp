#include <limits.h>
#include "gtest/gtest.h"
#include "utils/args/dc_args.h"

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
};

TEST_F(ArgsTest, IsSrcInOptions)
{
    ASSERT_EQ(false, args.hasKey(Options::SRC_FILE));
}


