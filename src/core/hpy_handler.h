#ifndef HPY_CORE_HPY_HANDLER_
#define HPY_CORE_HPY_HANDLER_

#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#include "collections/hpy_threadsafe_queue.h"
#endif

#ifndef HPY_CORE_HPY_HTTPMESSAGE_
#include "core/hpy_httpmessage.h"
#endif

#include <iostream>
#include <string>

class Handler
{
public:
    Handler();
    Handler(int conn_fd, bool is_https);
    bool RunHandlerService();
    std::string GetIp(std::string host);
    bool ConnectServer(std::string server_ip);
         
private:
    bool does_get_host_;
    bool is_https_;
    const int client_fd_;
    int server_fd_;
    std::string server_ip_;
    std::string host_;
    bool HandlerService();
    int MyRead(int fd, void *ptr, int n);
    int MyWrite(int fd, const void *buff, int n);
    
};

#endif