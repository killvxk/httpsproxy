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

Proxy::Proxy():kProxyServerPort_(hpy::Proxy::kProxyServerDefaultPort),\
              :kMaxConnections_(hpy::Proxy::kMaxConnections)
{
    Init();
}

Proxy::Proxy(int max_connections):kProxyServerPort_(hpy::Proxy::kProxyServerDefaultPort),\
                                   :kMaxConnections_(max_connections)
{
    Init();
}

bool Proxy::Init()
{
    current_connection_num_ = 0;
}

bool Proxy::RunProxyService()
{
    ProxyService();
}

bool Proxy::ProxyService()
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t client_scoket_len;
    struct sockaddr_in client_addr, server_addr;
    //when protocol is 0, if the type is stream, which means tcp; if the type is datagram, means udp  
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    if (bind(listen_fd, (SA *)&server_addr, sizeof(server_addr)) == -1)
        return 0;
    listen(listen_fd, LISTENQ);
    signal(SIGCHLD, sig_child);
    for( ; ; )
    {
        client_scoket_len = sizeof(client_addr);
        if( (conn_fd = accept(listen_fd, (SA *)&client_addr, &client_scoket_len)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                printf("accept error\n");
        }
        if( (child_pid = fork()) == 0)
        {
            close(listen_fd);
            str_echo(conn_fd);
            exit(0);
        }
        close(conn_fd);
    }
    return 0;
}
