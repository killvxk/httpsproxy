#ifndef HPY_CORE_HPY_HTTPMESSAGE_
#define HPY_CORE_HPY_HTTPMESSAGE_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#ifndef HPY_CORE_HPY_TLS_
#include "core/hpy_tls.h"
#endif

#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

class HttpMessage
{
public:
    HttpMessage();
    HttpMessage(char *buff, int n, bool is_https);
    bool Init(char *buff, int n, bool is_https);
    std::string GetHost();

private:
    char *buff_;
    int buff_lenth_;
    bool is_https_;
    std::string GetHostFromHttp();
    std::string GetHostFromHttps();
};

#endif

