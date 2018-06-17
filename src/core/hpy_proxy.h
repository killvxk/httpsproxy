#ifndef HPY_CORE_HPY_PROXY_
#define HPY_CORE_HPY_PROXY_ 

#ifndef HPY_CORE_HPY_HANDLER_
#include "core/hpy_handler.h"
#endif

#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#include "collections/hpy_threadsafe_queue.h"
#endif

#include <iostream>
#include <vector>

class Proxy
{
public:
    Proxy();
    Proxy(int max_connections);
    bool RunProxyService();

private:
    const int kMaxConnections_;
    static int current_connection_num_;

    bool Init();
    static void ProxyServiceThread(bool is_https);
    static void ServiceThread(int conn_fd, bool is_https);

};

#endif
