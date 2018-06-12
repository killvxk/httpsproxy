#ifndef HPY_UTILS_HPY_STRINGUTIL_
#include "utils/hpy_stringutil.h"
#endif

std::vector<std::string> hpy::utils::stringutil::split(std::string src, std::string str_to_find)
{
    std::vector<std::string> pairs;
    int start = 0;
    int match_pos = 0;
    while( start < src.length() && (match_pos = src.find(str_to_find, start)) != std::string::npos)
    {
        if(start != match_pos)
            pairs.push_back(src.substr(start, match_pos-start));
        start = match_pos + str_to_find.length();
    }
    if( start < src.length())
        pairs.push_back(src.substr(start));
    return pairs;
}

std::string hpy::utils::stringutil::strip(std::string src, char c)
{
    int start = 0;
    while (start < src.length() && src[start] == c)
        start++;
    int end = src.length() - 1;
    while(end > 0 && src[end] == c)
        end--;
    return src.substr(start, end - start + 1);
}