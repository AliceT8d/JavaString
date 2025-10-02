#ifndef JSTRING_H
#define JSTRING_H

#include <cstddef>
#include <cstring>

namespace JavaString {
class Jstring {
    char* _ptr;
    std::size_t _size;
    std::size_t length;

public:
    Jstring(const char* str)
    {
        _size = std::strlen(str);
        _ptr = new char[_size + 1];
        std::strcpy(_ptr, str);
    }
    Jstring(const Jstring& js)
    {
        _size = js._size;
        _ptr = new char[_size + 1];
        std::strcpy(_ptr, js._ptr);
    }
};
};
#endif // JSTRING_H
