#ifndef HPY_CORE_HPY_TCP_
#define HPY_CORE_HPY_TCP_

#include <iostream>
#include <map>
#include <string>

class Tcp
{
public:
    std::string GetSrcIp();
    std::string GetSrcPort();

private:
    std::string src_ip;
    std::string src_port;

};

#endif

