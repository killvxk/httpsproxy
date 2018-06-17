#ifndef HPY_UTILS_ARGS_HPY_OPTIONS_H_
#define HPY_UTILS_ARGS_HPY_OPTIONS_H_

#include <iostream>
#include <map>

class Options
{
private:
    //option name and isHasValue
    std::map<std::string, bool> options_dict_;
public:
    static const std::string RUN_AS_CLINET;
    static const std::string RUN_AS_SERVER;
    static const std::string HTTPSPROXY_IP;
public:
    Options();
    bool DoesHaveKey(std::string key);
    bool DoesHaveValue(std::string key);
};

#endif