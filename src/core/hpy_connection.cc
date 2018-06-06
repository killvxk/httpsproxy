#ifndef HPY_CORE_HPY_CONNECTION_
#include "core/hpy_connection.h"

Connection::Connection(std::string src_ip, std::string src_port, std::string host)
{
    src_ip_ = src_ip;
    src_port_ = src_port;
    host_ = host;
    // get des_ip_ corresponding to the host_
}


#endif