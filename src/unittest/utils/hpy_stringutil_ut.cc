#include <limits.h>
#include "gtest/gtest.h"
#include "utils/hpy_stringutil.h"

TEST(SplitTest, NormalString_ShouldPass)
{
    std::string test_string("1=2");
    std::vector<std::string> pairs = hpy::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");
    ASSERT_EQ(pairs[1], "2");    
    ASSERT_EQ(pairs.size(), 2);
}

TEST(SplitTest, OnePairFormer_ShouldPass)
{
    std::string test_string("1=");
    std::vector<std::string> pairs = hpy::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs.size(), 1);
}

TEST(SplitTest, OnePairLatter_ShouldPass)
{
    std::string test_string("=1");
    std::vector<std::string> pairs = hpy::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs.size(), 1);
}

TEST(SplitTest, SplitWithNotAChar_ShouldPass)
{
    std::string test_string("1==2");
    std::vector<std::string> pairs = hpy::utils::stringutil::split(test_string, "==");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs[1], "2");    
    ASSERT_EQ(pairs.size(), 2);
}



TEST(StripTest, SimpleString_ShouldPass)
{
    std::string test_string("  fsfs  ");
    ASSERT_EQ(hpy::utils::stringutil::strip(test_string, ' '), "fsfs");    
}

TEST(StripTest, StringWithLF_ShouldPass)
{
    std::string test_string("fsfs\n");
    ASSERT_EQ(hpy::utils::stringutil::strip(test_string, '\n'), "fsfs");    
}

TEST(StripTest, StringWithNothingToStrip_ShouldPass)
{
    std::string test_string("fsfs ");
    ASSERT_EQ(hpy::utils::stringutil::strip(test_string, ' '), "fsfs");    
}



