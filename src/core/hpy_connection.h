#ifndef HPY_CORE_HPY_CONNECTION_
#define HPY_CORE_HPY_CONNECTION_

#include <iostream>
#include <string>

#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#include "collections/hpy_threadsafe_queue.h"
#endif

#ifndef HPY_CORE_HPY_TCP_
#include "core/hpy_tcp.h"
#endif

class Connection
{
public:
    Connection(std::string src_ip, std::string src_port, std::string host);

private:
    ThreadsafeQueue<Tcp> connection_tcp_queue_;
    std::string src_ip_;
    std::string src_port_;
    std::string host_;
    std::string des_ip_;
    static const std::string des_port_;
};

const std::string Connection::des_port_ = "443";

#endif