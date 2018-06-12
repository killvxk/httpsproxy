#ifndef HPY_LOGGING_HPY_LOGGING_
#include "logging/hpy_logging.h"
#endif

#include <cstdio>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <exception>

#ifndef HPY_UTILS_HPY_STRINGUTIL_
#include "utils/hpy_stringutil.h"
#endif

#ifndef HPY_LOGGING_HPY_CONST_
#include "logging/hpy_const.h"
#endif

Logging logging;

Logging::Logging():kConfigFilePath_("logging/hpy_logging.ini"), config()
{
    is_busy_ = false;
    if(access(kConfigFilePath_.c_str(), 0) == 0)
    {
        config.Init(kConfigFilePath_);
        std::string logfile_path = config.GetValue(hpy::Config::kLogFilePath);
        
        if(logfile_path == "")
            return ;
        ofs.open(logfile_path, std::ofstream::out | std::ofstream::app);
    }
}

Logging& Logging::WithFilenameAndLine(const std::string file_name, int line_no)
{
    file_name_ = file_name;
    line_no_ = line_no;
    return *(this);
}

std::string Logging::GetPrefix()
{
    return GetCurrentTime() + " "\
           + file_name_ + ":"\
           + std::to_string(line_no_);
}

bool Logging::Info(const std::string info)
{
    return WriteLine(GetPrefix() + " INFO: " + info + "\n");
}

std::string Logging::GetCurrentTime()
{
    time_t tt;
    time(&tt);
    char s[255];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S:", localtime(&tt));
    struct timeval tv;
    gettimeofday(&tv, NULL);
    std::string return_val(s);
    return_val += std::to_string(tv.tv_usec/1000);
    return return_val;
}

bool Logging::WriteLine(std::string content)
{
    try
    {
        std::unique_lock<std::mutex> lock(mux_);
        while (is_busy_ == true)
            cond_.wait(lock);
        ofs.write(content.c_str(), content.length());
        is_busy_ = false;
        cond_.notify_one();
        return true;
    }
    catch(std::exception &e)
    {
        return false;
    }

}