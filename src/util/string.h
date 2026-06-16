#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string>
#include <algorithm>

namespace util::string
{

inline constexpr bool is_special(char c)
{
    return c == '.' || c == '-' || c == '\'' || c == '/' || c == '(' || c == ')';
}

inline bool contains_special_chars(const std::string& line)
{
    return std::any_of(line.begin(), line.end(), is_special);
}

inline std::string to_upper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::toupper(c));
        });

    return str;
}

} // namespace util

#endif // UTIL_STRING_H