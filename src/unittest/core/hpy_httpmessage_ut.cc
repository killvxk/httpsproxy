#include <limits.h>
#include <cstdio>
#include "gtest/gtest.h"
#include "core/hpy_httpmessage.h"

#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h> 

class HttpTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        char http_buff_[] = "GET/1.1\r\nHost: biying.com\r\nHost: biying.com\r\n\r\n";
        char *http_buff = (char*)malloc(sizeof(char)*100);
        strcpy(http_buff, http_buff_);
        http.Init(http_buff, 100, false);   

        int https_testfile;
        char *https_buff = (char*)malloc(sizeof(char)*200);
        if((https_testfile=open("unittest/core/qq.bin",O_RDONLY)) != -1)
        {
            read(https_testfile, https_buff, 200);
            https.Init(https_buff, 200, true); 
        }

        int https_testfile1;
        char *https_buff1 = (char*)malloc(sizeof(char)*200);
        if((https_testfile1=open("unittest/core/qq1.bin",O_RDONLY)) != -1)
        {
            read(https_testfile1, https_buff1, 200);
            https1.Init(https_buff1, 200, true); 
        }
    }
    virtual void TearDown() {
        ;
    }
    HttpMessage http;
    HttpMessage https;
    HttpMessage https1;
};


TEST_F(HttpTest, HttpGetHost_ShouldPass)
{
    ASSERT_EQ("biying.com", http.GetHost());
}

TEST_F(HttpTest, HttpsGetHost_ShouldPass)
{
    ASSERT_EQ("cn.bing.com", https.GetHost());
}

TEST_F(HttpTest, Https1GetHost_ShouldPass)
{
    ASSERT_EQ("cn.bing.com", https1.GetHost());
}