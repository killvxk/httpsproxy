#ifndef HPY_LOGGING_HPY_LOGGING_
#define HPY_LOGGING_HPY_LOGGING_

#define LOG (logging.WithFilenameAndLine(__FILE__, __LINE__))

#include <iostream>
#include <map>
#include <fstream>
#include <mutex>
#include <condition_variable>

#ifndef HPY_LOGGING_HPY_CONFIG_
#include "logging/hpy_config.h"
#endif

class Logging
{
public:
    Logging();
    Logging& WithFilenameAndLine(const std::string file_name, int line_no);
    bool Debug(const std::string info);
    bool Info(const std::string info);
    bool Warn(const std::string info);
    bool Error(const std::string info);
    static std::string GetCurrentTime();

private:
    std::string file_name_;
    int line_no_;
    const std::string kConfigFilePath_;
    Config config;
    std::ofstream ofs;
    bool is_busy_;
    std::mutex mux_;
    std::condition_variable cond_;
    
    std::string GetPrefix();
    bool WriteLine(std::string content);

};

extern Logging logging;

#endif