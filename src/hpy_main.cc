
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
        return 0;
    }
    catch(exception& e)
    {
        return 0;
    }
}