#ifndef HPY_CORE_HPY_HTTPMESSAGE_
#include "core/hpy_httpmessage.h"
#endif

#include <string>
#include <sstream>
#include <vector>

#ifndef HPY_UTILS_HPY_STRINGUTIL_
#include "utils/hpy_stringutil.h"
#endif

HttpMessage::HttpMessage(void *buff, int n, bool is_https)
{
    Init((char*)buff, n, is_https);
}

HttpMessage::HttpMessage()
{
    Init(NULL, 0, false);
}

bool HttpMessage::Init(char *buff, int n, bool is_https)
{
    buff_ = buff;
    buff_lenth_ = n;
    is_https_ = is_https;
    return true;
}

std::string HttpMessage::GetHost()
{
    if(is_https_ == false)
        return GetHostFromHttp();
    else
        return GetHostFromHttps();
}

std::string HttpMessage::GetHostFromHttp()
{
    std::string line;
    std::stringstream ss(buff_);
    while(std::getline(ss, line))
    {
        if(line.find("host") == 0 || line.find("Host") == 0)
        {
            line = hpy::utils::stringutil::strip(line, '\r');
            std::vector<std::string> pairs = hpy::utils::stringutil::split(line, ":");
            if(pairs.size() == 2)
                return hpy::utils::stringutil::strip(pairs[1], ' ');
        }
        line.clear();
    }
    LOG.Error(std::to_string(errno));
    LOG.Info("get host from http failed");
    return "";
}

std::string HttpMessage::GetHostFromHttps()
{
    int pos = 1 + 2 + 2;
    pos += 1 + 3 + 2;
    pos += 32;
    //session id
    pos += buff_[pos];
    pos += 1;
    //cipher
    pos += (buff_[pos] << 8) + buff_[pos + 1];
    pos +=2;
    //compression method
    pos += buff_[pos];
    pos += 1;
    if(pos != buff_lenth_)
    {//has extensions
        //extensions length
        unsigned short extensions_length = (buff_[pos] << 8) + buff_[pos + 1];
        pos += 2;
        while ( extensions_length != 0 && pos != buff_lenth_)
        {
            if((buff_[pos] << 8) + buff_[pos + 1] == 0x0000)
            {//server_name
                
                pos += 2;       //type
                pos += 2;       //length
                pos += 2;       //server name list length
                if(buff_[pos] == 0x00)
                {//server name type
                    pos += 1;
                    unsigned short server_name_length = (buff_[pos] << 8) + buff_[pos + 1];
                    pos += 2;
                    char server_name[server_name_length + 1];
                    int i;
                    for(i = 0; i<server_name_length; i++)
                        server_name[i] = buff_[pos + i];
                    server_name[i] = '\0';
                    return server_name;
                }
            }
            else
            {
                pos += 2;
                pos += (buff_[pos] << 8) + buff_[pos + 1];
                pos += 2;
            }
            
        }
    }
    return "";
}

