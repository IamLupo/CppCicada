#ifndef UTIL_UTF8_H
#define UTIL_UTF8_H

#include <stdexcept>

namespace util
{
inline size_t utf8_char_length(unsigned char c)
{
    if ((c & 0x80) == 0x00) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;

    throw std::runtime_error("Invalid UTF-8");
}
}
#endif // UTIL_UTF8_H