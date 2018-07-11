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

#ifndef HPY_CORE_HPY_DECRYPTION_
#include "core/hpy_decryption.h"
#endif

#ifndef HPY_CORE_HPY_ENCRYPTION_
#include "core/hpy_encryption.h"
#endif

#ifndef HPY_UTILS_ARGS_HPY_ARGS_H_
#include "utils/args/hpy_args.h"
#endif

#ifndef HPY_UTILS_ARGS_HPY_ARGS_H_
#include "utils/args/hpy_options.h"
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
    unsigned char buff[hpy::Tcp::kMaxDataLength];
    int keep_alive = 1;
    setsockopt(client_fd_, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive));

    bool is_run_as_server = args.HasKey(Options::RUN_AS_SERVER);
    for( ; ; )
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(client_fd_, &rset))
        {
            if( (n = read(client_fd_, buff, hpy::Tcp::kMaxDataLength)) == 0)
                break;
            else if(n == -1)
            {
                if(errno != EINTR)
                {
                    LOG.Error("errno: " + std::to_string(errno));
                    break;
                }
            }
            else
            {
                LOG.Debug("1, " + std::to_string(n));
                if(is_run_as_server)
                    hpy::Tcp::Decryption::Decrypt(hpy::Tcp::Encryption::kCaesarCipher, buff, n, hpy::Tcp::Encryption::kCaesarCipherDefaultKey);
                else
                    hpy::Tcp::Encryption::Encrypt(hpy::Tcp::Encryption::kCaesarCipher, buff, n, hpy::Tcp::Encryption::kCaesarCipherDefaultKey);
                if(does_get_host_ == false)
                {
                    if(is_run_as_server == true)
                    {
                        HttpMessage httpmessage(buff, n, is_https_);
                        host_ = httpmessage.GetHost();
                        LOG.Info("host: " + host_);
                        if(host_ == "" || (server_ip_ = GetIp(host_)) == "")
                            break;
                    }
                    else
                    {
                        host_ = "httpsproxy";
                        server_ip_ = args.Get(Options::HTTPSPROXY_IP);
                    }
                    LOG.Info(host_ + ":" + server_ip_);
                    if (ConnectServer(server_ip_) == true)
                    {
                        does_get_host_ = true;
                        FD_SET(server_fd_, &allset);
                        maxfd = maxfd > server_fd_ ? maxfd : server_fd_;
                        setsockopt(server_fd_, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive));
                    }
                    else
                        break;
                }   
                n = write(server_fd_, buff, n);   
                LOG.Debug("2, " + std::to_string(n));
            }
        }
        if(server_fd_ != -1 && FD_ISSET(server_fd_, &rset))
        {
            if( (n = read(server_fd_, buff, hpy::Tcp::kMaxDataLength)) == 0)
                break;
            else if(n == -1)
            {
                if(errno != EINTR)
                {
                    LOG.Error("errno: " + std::to_string(errno));
                    break;
                }
            }
            else
            {
                LOG.Debug("3, " + std::to_string(n));
                if(is_run_as_server == false)
                    hpy::Tcp::Decryption::Decrypt(hpy::Tcp::Encryption::kCaesarCipher, buff, n, hpy::Tcp::Encryption::kCaesarCipherDefaultKey);
                else
                    hpy::Tcp::Encryption::Encrypt(hpy::Tcp::Encryption::kCaesarCipher, buff, n, hpy::Tcp::Encryption::kCaesarCipherDefaultKey);
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

bool Handler::ConnectServer(std::string server_ip)
{
    struct sockaddr_in server_addr;
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(is_https_ == true)
        if(args.HasKey(Options::RUN_AS_SERVER) == true)
            server_addr.sin_port = htons(hpy::Proxy::kHttpsDefaultPort);
        else
            server_addr.sin_port = htons(hpy::Proxy::kHttpsDefaultProxyPort);
    else
        if(args.HasKey(Options::RUN_AS_SERVER) == true)
            server_addr.sin_port = htons(hpy::Proxy::kHttpDefaultPort);
        else
            server_addr.sin_port = htons(hpy::Proxy::kHttpDefaultProxyPort);
    inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);
    if (connect(server_fd_, (SA *)&server_addr, sizeof(server_addr)) < 0)
    {
        LOG.Error("conn to " + server_ip + " failed, errno: " + std::to_string(errno));
        return false;
    }
    else
    {
        LOG.Info("conn to " + server_ip + " successfully");
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
