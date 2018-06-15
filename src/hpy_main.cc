
#ifndef HPY_CORE_HPY_PROXY_
#include "core/hpy_proxy.h"
#endif

#include <iostream>
#include <fstream>
#include <exception>

#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

int main(int argc,char *argv[])
{
    try
    {
        LOG.Info("start httpsproxy");
        Proxy proxy;
        proxy.RunProxyService();
        return 0;
    }
    catch(std::exception& e)
    {
        LOG.Error(e.what());
        return -1;
    }
}