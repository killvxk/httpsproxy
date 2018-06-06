#ifndef HPY_CORE_HPY_PROXY_
#define HPY_CORE_HPY_PROXY_ 

#ifndef HPY_CORE_HPY_TCP_
#include "core/hpy_tcp.h"
#endif

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
    Proxy(int tcp_queue_capacity);
    bool RunProxyService();

private:
    const int kTcpQueueCapacity_;
    ThreadsafeQueue<Tcp> proxy_tcp_queue_;
    Handler *handler_;

    bool Init();
    static bool ProxyService();

};

#endif
