#ifndef UTIL_UTF8_H
#define UTIL_UTF8_H

namespace util::utf8
{

inline size_t char_length(unsigned char c)
{
    if ((c & 0x80) == 0x00) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;

    return -1;
}

} // namespace util

#endif // UTIL_UTF8_H