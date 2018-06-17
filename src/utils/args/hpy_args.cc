#ifndef HPY_UTILS_ARGS_HPY_ARGS_H_
#include "utils/args/hpy_args.h"
#endif

#include <cstring>

Args args;

void Args::Set(std::string key, std::string value)
{
    arg_dict_[key] = value;
}

bool Args::DoesOnlyHaveSrc()
{
    return arg_dict_.size() == 1;
}

bool Args::HasKey(std::string key)
{
    if (arg_dict_.find(key) != arg_dict_.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Args::Get(std::string key)
{
    if (HasKey(key) == true)
    {
        return arg_dict_[key];
    }
    else
    {
        return "";
    }
}

bool Args::ParseArgs(int argc, char *argv[])
{
    int i = 1;
    int addend = 0;
    while (i < argc)
    {
        char *option = argv[i];
        if (option[0] == '-')
        {
            if (strlen(option) >= 2 and option[1] == '-')
            {
                addend = ParseArgsStartsWithDoubleStrikethrough(option);
            }
            else
            {
                addend = ParseArgsStartsWithSingleStrikethrough(option, i+1<argc?(argv[i+1]):NULL);
            }
        }
        if (addend == -1)
            return false;
        i += addend;
    }
    return true;
}

int Args::ParseArgsStartsWithSingleStrikethrough(char *option, char *value)
{
    if (strlen(option) == 2)
    {
        if (all_options_.DoesHaveKey(CharToString(option[1])))
        {
            if (all_options_.DoesHaveValue(CharToString(option[1])))
            {
                if (value != NULL)
                {
                    arg_dict_[CharToString(option[1])] = std::string(value);
                    return 2;
                }
                else
                {
                    OptionError::NotWithValue(std::string(option));
                    return -1;
                }
            }
            else
            {
                arg_dict_[CharToString(option[1])] = std::string();
                return 1;
            }
        }
        else
        {
            OptionError::NotHaveThisOption(std::string(option));
            return -1;
        }
    }
    else
    {
        for (int j = 1; j < strlen(option); j++)
        { 
            if (all_options_.DoesHaveKey(CharToString(option[j])))
            {
                if (all_options_.DoesHaveValue(CharToString(option[j])) == false)
                {
                    Set(CharToString(option[j]), std::string());
                }
                else
                {
                    OptionError::NotWithValue(CharToString(option[j]));
                    return -1;
                }
            }
            else
            {
                OptionError::NotHaveThisOption(CharToString(option[j]));
                return -1;
            }
            
        }
        return 1;
    }
}

int Args::ParseArgsStartsWithDoubleStrikethrough(char *option)
{
    if (all_options_.DoesHaveKey(std::string(option)))
    {
        Set(std::string(option), std::string());
        return 1;
    }
    else
    {   OptionError::NotHaveThisOption(std::string(option));
        return -1;
    }
    return 1;
}

std::string Args::CharToString(char ch)
{
    char a[2] = {ch, '\0'};
    return std::string(a);
}