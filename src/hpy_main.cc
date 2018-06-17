
#ifndef HPY_CORE_HPY_PROXY_
#include "core/hpy_proxy.h"
#endif

#include <iostream>
#include <fstream>
#include <exception>

#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

#ifndef HPY_UTILS_ARGS_HPY_ARGS_H_
#include "utils/args/hpy_args.h"
#endif

int main(int argc,char *argv[])
{
    try
    {   
        if (args.ParseArgs(argc, argv) == false )
            return -1;
        if( args.HasKey(Options::RUN_AS_CLINET) && args.Get(Options::HTTPSPROXY_IP) == "" )
        {
            LOG.Error("must set httpsproxy ip when run as client");
            return -1;
        }
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