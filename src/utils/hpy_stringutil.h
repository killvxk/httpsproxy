#ifndef HPY_UTILS_HPY_STRINGUTIL_
#define HPY_UTILS_HPY_STRINGUTIL_

#include <iostream>
#include <vector>

namespace hpy
{
    namespace utils
    {
        namespace stringutil
        {
            std::vector<std::string> split(std::string src, std::string str_to_find);
            std::string strip(std::string src,char c); 

        };//stringutil
    };//utils

};//hpy
#endif