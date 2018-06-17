#include <limits.h>
#include "gtest/gtest.h"
#include "core/hpy_handler.h"

class HandlerTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    Handler handler;
};

TEST_F(HandlerTest, GetIp_ShouldPass)
{
    ASSERT_NE("", handler.GetIp("bing.com"));
}

TEST_F(HandlerTest, ConnectServer_ShouldPass)
{
    ASSERT_EQ(true, handler.ConnectServer(handler.GetIp("bing.com")));
}

