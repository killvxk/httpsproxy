#ifndef HPY_UTILS_ARGS_HPY_ARGS_H_
#define HPY_UTILS_ARGS_HPY_ARGS_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>

#ifndef HPY_UTILS_ARGS_HPY_OPTIONS_H_
#include "utils/args/hpy_options.h"
#endif

#ifndef HPY_UTILS_ARGS_HPY_OPTION_ERROR_H_
#include "utils/args/hpy_option_error.h"
#endif

class Args
{
public:
    Args(){}
    bool ParseArgs(int argc, char *argv[]);
    void Set(std::string, std::string value);
    std::string Get(std::string key);
    bool HasKey(std::string key);
    bool DoesOnlyHaveSrc();

private:
    Options all_options_;
    std::map<std::string, std::string> arg_dict_;
    int ParseArgsStartsWithSingleStrikethrough(char *option, char *value);
    int ParseArgsStartsWithDoubleStrikethrough(char *option);
    std::string CharToString(char ch);

};
extern Args args;
#endif