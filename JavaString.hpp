#ifndef JSTRING_H
#define JSTRING_H

#include <cstddef>
#include <cstring>
#include <iostream>

namespace JavaString {
class Jstring {
    char* _ptr;
    std::size_t _size;
    // std::size_t length;

    Jstring(char* ptr, std::size_t size)
        : _ptr(ptr), _size(size)
    {
    }

public:
    Jstring()
    {
        _size = 0;
        _ptr = new char[1];
        _ptr[0] = '\0';
    }

    Jstring(const char* str)
    {
        if (str == nullptr) throw std::invalid_argument("传入的参数是一个空指针！");
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

    Jstring& operator=(const Jstring& js)
    {
        _size = js._size;
        _ptr = new char[_size + 1];
        std::strcpy(_ptr, js._ptr);
        return *this;
    }

    Jstring operator+(const Jstring& js) const
    {
        auto size = _size + js._size;
        char* ptr = new char[size + 1];
        std::strcpy(ptr, _ptr);
        std::strcat(ptr, js._ptr);

        return Jstring(ptr, size);
    }

    Jstring operator+(const char* str) const
    {
        if (str == nullptr) throw std::invalid_argument("传入的参数是一个空指针！");
        auto size = _size + std::strlen(str);
        char* ptr = new char[size + 1];
        std::strcpy(ptr, _ptr);
        std::strcat(ptr, str);

        return Jstring(ptr, size);
    }

    friend std::ostream& operator<<(std::ostream& os, const Jstring& js)
    {
        os << "[" << js._ptr << "]";
        return os;
    }

    ~Jstring()
    {
        delete[] _ptr;
    }
};
};
#endif // JSTRING_H
