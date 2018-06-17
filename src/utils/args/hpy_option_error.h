#ifndef HPY_UTILS_HPY_OPTION_ERROR_H_
#define HPY_UTILS_HPY_OPTION_ERROR_H_

#include <iostream>
class OptionError
{
public:
    static void NotHaveThisOption(std::string option);
    static void NotWithValue(std::string option);
    static void NotHaveSourceFile();
};

#endif