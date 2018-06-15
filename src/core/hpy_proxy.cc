#ifndef HPY_CORE_HPY_PROXY_
#include "core/hpy_proxy.h"
#endif

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <thread>

#ifndef HPY_CORE_HPY_CONST_
#include "core/hpy_const.h"
#endif

#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

typedef struct sockaddr SA; 

Proxy::Proxy():kMaxConnections_(hpy::Proxy::kMaxConnections)
{
    Init();
}

Proxy::Proxy(int max_connections):kMaxConnections_(max_connections)
{
    Init();
}

bool Proxy::Init()
{
    current_connection_num_ = 0;
    return true;
}

bool Proxy::RunProxyService()
{
    return ProxyService();
}

bool Proxy::ProxyService()
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t client_scoket_len;
    struct sockaddr_in client_addr, server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    pid_t pid;
    if((pid =fork()) < 0)
        LOG.Error("fork error");
    else if(pid == 0)
        server_addr.sin_port = htons(hpy::Proxy::kHttpDefaultPort);
    else
        server_addr.sin_port = htons(hpy::Proxy::kHttpsDefaultPort);
    //when protocol is 0, if the type is stream, which means tcp; if the type is datagram, means udp  
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(listen_fd, (SA *)&server_addr, sizeof(server_addr)) == -1)
    {
        LOG.Error("bind error, errno:" + std::to_string(errno));
        return false;
    }
    listen(listen_fd, hpy::Proxy::kListenQ);
    for( ; ; )
    {
        client_scoket_len = sizeof(client_addr);
        if( (conn_fd = accept(listen_fd, (SA *)&client_addr, &client_scoket_len)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                LOG.Error("accept error");
        }
        std::thread th(ServiceThread, conn_fd, pid == 0 ? false : true);
        th.detach();
        current_connection_num_ ++;
        LOG.Info("accept " + std::string(pid==0?"http":"https") + " conn, current connection num:" + std::to_string(current_connection_num_));
    }
    return true;
}

void Proxy::ServiceThread(int conn_fd, bool is_https)
{
    Handler handler(conn_fd, is_https);
    handler.RunHandlerService();
}
