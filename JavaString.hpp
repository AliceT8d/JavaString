#ifndef JSTRING_H
#define JSTRING_H

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

namespace JavaString {
class Jstring {
    char* _ptr;
    size_t _size;

    Jstring(char* ptr, size_t size)
        : _ptr(ptr), _size(size)
    {
    }

    char* _getMem() const
    {
        return new char[_size + 1];
    }

    char* _getMem(size_t size) const
    {
        return new char[size + 1];
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
        if (this != &js) {
            delete[] _ptr;
            _size = js._size;
            _ptr = new char[_size + 1];
            std::strcpy(_ptr, js._ptr);
        }
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

    char operator[](size_t index) const
    {
        return charAt(index);
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

    size_t length() const
    {
        return _size;
    }
    bool isEmpty() const
    {
        return _size == 0;
    }
    char charAt(size_t index) const
    {
        if (index >= _size) throw std::out_of_range("访问位置超过数组长度！");
        return _ptr[index];
    }

    std::vector<char> toCharVector() const
    {
        return std::vector<char>(_ptr, _ptr + _size);
    }

    /*
     * 取 [beginIndex, min(_size, endIndex)) 之间的字符串
     */
    Jstring substring(size_t beginIndex, size_t endIndex = SIZE_MAX) const
    {
        if (beginIndex > _size)
            throw std::out_of_range("beginIndex > length");
        if (endIndex == SIZE_MAX)
            endIndex = _size;
        if (endIndex < beginIndex or endIndex > _size)
            throw std::out_of_range("endIndex out of range");

        size_t newSize = endIndex - beginIndex;
        char* ptr = new char[newSize + 1];
        std::memcpy(ptr, _ptr + beginIndex, newSize);
        ptr[newSize] = '\0';
        return Jstring(ptr, newSize);
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

    Jstring replace(char oldChar, char newChar) const
    {
        char* ptr = _getMem();
        for (size_t i = 0; _ptr[i] != '\0'; ++i) {
            if (_ptr[i] == oldChar) {
                ptr[i] = newChar;
                continue;
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

    bool contains(const Jstring& js) const
    {
        auto result = std::strstr(_ptr, js._ptr);
        return result != nullptr;
    }

    std::string toString() const
    {
        return std::string(_ptr);
    }

    /*
     * 判断 _ptr 在 toffset 位置是否以 prefix 开头
     * 检测空字符串时，总是为真
     */
    bool startsWith(const Jstring& prefix, size_t toffset = 0) const
    {
        if (prefix.isEmpty()) return true;
        if (toffset >= _size or prefix._size > _size - toffset)
            return false;
        for (size_t index = 0; index != prefix._size; ++index) {
            if (_ptr[index + toffset] != prefix._ptr[index])
                return false;
        }
        return true;
    }

    int64_t indexOf(char ch, size_t fromIndex = 0) const
    {
        if (fromIndex >= _size) return -1;
        for (; fromIndex != _size; ++fromIndex) {
            if (_ptr[fromIndex] == ch) return fromIndex;
        }
        return -1;
    }

    int64_t indexOf(const Jstring& js, size_t fromIndex = 0) const
    {
        if (js._size == 0) {
            if (fromIndex < _size)
                return static_cast<int64_t>(fromIndex);
            return -1;
        }
        if (fromIndex >= _size or js._size > _size - fromIndex) return -1;

        const char* start = _ptr + fromIndex;
        const char* end = _ptr + (_size - js._size + 1);

        for (const char* p = start; p != end; ++p) {
            if (std::memcmp(p, js._ptr, js._size) == 0) {
                return static_cast<int64_t>(p - _ptr);
            }
        }
        return -1;
    }

    Jstring trim() const
    {
        if (this->isEmpty()) return *this;
        size_t begin {}, end { _size - 1 };
        while (begin < _size && isspace(static_cast<unsigned char>(_ptr[begin]))) {
            ++begin;
        }
        while (end > begin && isspace(static_cast<unsigned char>(_ptr[end]))) {
            --end;
        }
        if (begin > end)
            return Jstring();

        auto size = end - begin + 1;
        auto ptr = _getMem(size);
        std::memcpy(ptr, _ptr + begin, size);
        ptr[size] = '\0';
        return Jstring(ptr, size);
    }
};
};
#endif // JSTRING_H
