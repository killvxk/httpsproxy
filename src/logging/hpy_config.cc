#ifndef HPY_LOGGING_HPY_CONFIG_
#include "logging/hpy_config.h"
#endif

#include <cstdio>
#include <iostream>
#include <fstream>
#include <iterator>

#ifndef HPY_UTILS_HPY_STRINGUTIL_
#include "utils/hpy_stringutil.h"
#endif

#ifndef HPY_LOGGING_HPY_CONST_
#include "logging/hpy_const.h"
#endif

Config::Config()
{
    config_items_[hpy::Config::kLogFilePath] = "";
}

bool Config::Init(std::string config_file_path)
{
    std::ifstream ifs(config_file_path, std::ifstream::in);
    if(!ifs.is_open())
        return false;
    std::string line;
    while(! ifs.eof())
    {
        std::getline(ifs, line);
        if(line.length() == 0 || line[0] == '\n' || line[0] == '#')
            continue;
        line = hpy::utils::stringutil::strip(line, '\n');
        std::vector<std::string> pairs = hpy::utils::stringutil::split(line, "=");
        for(std::vector<std::string>::iterator it = pairs.begin(); it != pairs.end(); it++)
            *it = hpy::utils::stringutil::strip(*it, ' ');
        if(pairs.size() == 0 || pairs.size() > 2 || config_items_.find(pairs[0]) == config_items_.end())
            return false;
        if(pairs.size() == 2)
            config_items_[pairs[0]] = pairs[1];
    }
    return false;
}


std::string Config::GetValue(std::string key)
{
    return IsHave(key) == false ? "" : config_items_[key];
}

bool Config::IsHave(std::string key)
{
    return config_items_.find(key) == config_items_.end() ? false : true;
}
