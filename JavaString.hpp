#ifndef JSTRING_H
#define JSTRING_H

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace JavaString {
class Jstring {
    char* _ptr;
    std::size_t _size;
    // std::size_t length;

    Jstring(char* ptr, std::size_t size)
        : _ptr(ptr), _size(size)
    {
    }

    char* _getMem() const
    {
        return new char[_size + 1];
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

    std::size_t length() const
    {
        return _size;
    }
    bool isEmpty() const
    {
        return _size == 0;
    }
    char charAt(std::size_t index) const
    {
        if (index >= _size) throw std::out_of_range("访问位置超过数组长度！");
        return _ptr[index];
    }

    /*
     * 函数的返回内部_ptr的副本，请及时delete
     */
    char* toCharArray() const
    {
        char* copy = new char[_size + 1];
        std::strcpy(copy, _ptr);
        return copy;
    }

    /*
     * 取 [beginIndex, min(_size - 1, endIndex)] 之间的字符串
     */
    Jstring substring(size_t beginIndex, size_t endIndex = SIZE_MAX) const
    {
        if (beginIndex >= endIndex or beginIndex >= _size)
            throw std::out_of_range("参数不合法！");
        endIndex = std::min(_size - 1, endIndex);
        auto size = endIndex - beginIndex + 1;
        char* ptr = new char[size + 1];
        for (size_t i = 0; i != size; ++i)
            ptr[i] = _ptr[beginIndex + i];
        ptr[size] = '\0';
        return Jstring(ptr, size);
    }

    bool equals(const Jstring& js) const
    {
        if (_size != js._size) return false;
        return not std::strcmp(_ptr, js._ptr);
    }

    bool equalsIgnoreCase(const Jstring& js) const
    {
        if (_size != js._size) return false;
        for (size_t i = 0; i != _size; ++i) {
            if (tolower(_ptr[i]) != tolower(js._ptr[i])) {
                return false;
            }
        }
        return true;
    }

    Jstring replace(char oldChar, char newChar)
    {
        char* ptr = _getMem();
        for (size_t i = 0; _ptr[i] != '\0'; ++i) {
            if (_ptr[i] == oldChar) {
                ptr[i] = newChar;
            }
            ptr[i] = _ptr[i];
        }
        return Jstring(ptr, _size);
    }

    Jstring concat(const Jstring& js) const
    {
        return (*this) + js;
    }

    Jstring toUpperCase() const
    {
        char* ptr = _getMem();
        for (size_t i = 0; _ptr[i] != '\0'; ++i) {
            ptr[i] = toupper(_ptr[i]);
        }
        return Jstring(ptr, _size);
    }

    Jstring toLowerCase() const
    {
        char* ptr = _getMem();
        for (size_t i = 0; _ptr[i] != '\0'; ++i) {
            ptr[i] = tolower(_ptr[i]);
        }
        return Jstring(ptr, _size);
    }
};
};
#endif // JSTRING_H
