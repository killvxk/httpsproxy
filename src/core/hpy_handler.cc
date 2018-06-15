#ifndef HPY_CORE_HPY_HANDLER_
#include "core/hpy_handler.h"
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
#include <netdb.h>
#include <sys/select.h>

#ifndef HPY_CORE_HPY_CONST_
#include "core/hpy_const.h"
#endif

#ifndef HPY_CORE_HPY_HTTPMESSAGE_
#include "core/hpy_httpmessage.h"
#endif

#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

typedef struct sockaddr SA; 

Handler::Handler():client_fd_(-1)
{
    does_get_host_ = false;
    is_https_ = false;
    server_fd_ = -1;
    host_ = "";
    server_ip_ = "";
}

Handler::Handler(int client_fd, bool is_https):client_fd_(client_fd)
{
    does_get_host_ = false;
    is_https_ = is_https;
    server_fd_ = -1;
    host_ = "";
    server_ip_ = "";
}

bool Handler::RunHandlerService()
{
    return HandlerService();
}

bool Handler::HandlerService()
{
    //select
    fd_set rset, allset;
    FD_ZERO(&allset);
    FD_SET(client_fd_, &allset);
    int nready, maxfd;
    maxfd = client_fd_;

    int n;
    char buff[hpy::Tcp::kMaxDataLength];
    for( ; ; )
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(client_fd_, &rset))
        {
            if( (n = read(client_fd_, buff, hpy::Tcp::kMaxDataLength)) == 0)
                break;
            else
            {
                if(does_get_host_ == false)
                {
                    HttpMessage httpmessage(buff, n, is_https_);
                    host_ = httpmessage.GetHost();
                    LOG.Info("host: " + host_);
                    if(host_ != "")
                    {
                        if (ConnectServer(host_) == true)
                        {
                            does_get_host_ = true;
                            FD_SET(server_fd_, &allset);
                            maxfd = maxfd > server_fd_ ? maxfd : server_fd_;
                        }
                        else
                            break;
                    }
                }
                LOG.Debug("1, " + std::to_string(n));
                n = write(server_fd_, buff, n);   
                LOG.Debug("2, " + std::to_string(n));
            }
        }
        if(server_fd_ != -1 && FD_ISSET(server_fd_, &rset))
        {
            if( (n = read(server_fd_, buff, hpy::Tcp::kMaxDataLength)) == 0)
                break;
            else
            {
                LOG.Debug("3, " + std::to_string(n));
                n = write(client_fd_, buff, n);   
                LOG.Debug("4, " + std::to_string(n));
            }
        }
    }
    close(client_fd_);
    if(server_fd_ != -1)
        close(server_fd_);
    LOG.Info("closed the conn to " + host_);
    return true;
}

bool Handler::ConnectServer(std::string host)
{
    if((server_ip_ = GetIp(host)) == "")
        return false;
    LOG.Info(host + " : " + server_ip_);
    struct sockaddr_in server_addr;
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(is_https_ == true)
        server_addr.sin_port = htons(hpy::Proxy::kHttpsDefaultPort);
    else
        server_addr.sin_port = htons(hpy::Proxy::kHttpDefaultPort);
    inet_pton(AF_INET, server_ip_.c_str(), &server_addr.sin_addr);
    if (connect(server_fd_, (SA *)&server_addr, sizeof(server_addr)) < 0)
    {
        LOG.Error("conn to " + host + " failed");
        return false;
    }
    else
    {
        LOG.Info("conn to " + host + " successfully");
        return true;
    }
}

std::string Handler::GetIp(std::string host)
{
    struct hostent *hptr;
    if((hptr = gethostbyname(host.c_str())) == NULL)
    {
        LOG.Error("gethostbyname failed, host:" + host );
        return "";
    }
    char str[INET_ADDRSTRLEN];
    char **pptr;
    switch(hptr->h_addrtype)
    {
        case AF_INET:
            for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
                return std::string(inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
            break;
        default:
            LOG.Error("unknown address type");
            break;
    }
    return "";
}

int Handler::MyRead(int fd, void *buff, int n)
{
    int nleft;
    int nread;
    char *ptr;
    ptr = (char*)buff;
    nleft = n;
    while(nleft > 0)
    {
        if( (nread = read(fd, ptr, nleft)) < 0)
        {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

int Handler::MyWrite(int fd, const void *buff, int n)
{
    int nleft;
    int nwritten;
    const char *ptr;
    ptr = (char*)buff;
    nleft = n;
    while (nleft > 0)
    {
        if( (nwritten = (fd, ptr, nleft)) <= 0)
        {
            if( nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}