#ifndef HPY_UTILS_ARGS_HPY_OPTIONS_H_
#include "utils/args/hpy_options.h"
#endif

const std::string Options::RUN_AS_CLINET = "--run-as-client"; 
const std::string Options::RUN_AS_SERVER = "--run-as-server"; 
const std::string Options::HTTPSPROXY_IP = "i";

Options::Options()
{
    options_dict_[RUN_AS_CLINET] = false;
    options_dict_[RUN_AS_SERVER] = false;
    options_dict_[HTTPSPROXY_IP] = true;
}

bool Options::DoesHaveKey(std::string key)
{
    if (options_dict_.find(key) != options_dict_.end())
        return true;
    else
        return false;
}

bool Options::DoesHaveValue(std::string key)
{
    if (DoesHaveKey(key) == true)
        return options_dict_[key];
    else
        return false;
}

