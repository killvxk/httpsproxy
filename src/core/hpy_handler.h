#ifndef HPY_CORE_HPY_HANDLER_
#define HPY_CORE_HPY_HANDLER_

#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#include "collections/hpy_threadsafe_queue.h"
#endif

#ifndef HPY_CORE_HPY_TCP_
#include "core/hpy_tcp.h"
#endif

#include <map>

class Handler
{
public:
    Handler(ThreadsafeQueue<Tcp> &thread_safe_queue);
    bool RunHandlerService();
         
private:
    ThreadsafeQueue<Tcp> &proxy_tcp_queue_;
    //std::string 格式为:src_ip+src_port
    std::map<std::string, ThreadsafeQueue<Tcp> & > connection_map_;
    bool Dispatcher();
    static bool HandlerService();
    ThreadsafeQueue<Tcp>& CreateConnection(std::string src_ip, std::string src_port, std::string host);
};

#endif