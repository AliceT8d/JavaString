# JavaString

一个模仿 Java `String` 类行为的 C++ 自定义字符串类 `Jstring`。`JavaString` 项目提供了一个名为 `Jstring` 的 C++ 类，其接口设计参考了 Java 中 `String` 类的常用方法，该类封装了 C 风格字符串（`char*`），并提供了安全、易用的高层接口。


## 常用方法

- `length()`, `isEmpty()`, `charAt()`
- `substring()`, `concat()`, `+` 拼接
- `equals()`, `equalsIgnoreCase()`
- `toUpperCase()`, `toLowerCase()`, `trim()`
- `startsWith()`, `contains()`, `indexOf()`
- `replace()`, `toCharVector()`, `toString()`

---

## 使用示例

```cpp
#include <iostream>
#include "Jstring.hpp"

using namespace JavaString;

int main() {
    Jstring s1("Hello");
    Jstring s2 = s1 + " World!";
    std::cout << s2 << std::endl;  // 输出: [Hello World!]

    Jstring s3 = s2.trim().toUpperCase();
    std::cout << s3 << std::endl;  // 输出: [HELLO WORLD!]

    if (s3.startsWith("HELLO")) {
        std::cout << "Starts with 'HELLO'" << std::endl;
    }

    auto idx = s3.indexOf('W');
    std::cout << "Index of 'W': " << idx << std::endl;  // 输出: 6

    return 0;
}
```


## 注意事项

- 本项目**仅用于学习目的**，不建议在生产环境中替代 `std::string`。
- 所有字符串操作均基于 ASCII 字符，未考虑 Unicode 或多字节编码。
- 内存管理完全由类内部控制，用户无需手动释放。



## 编译要求

- C++11 或更高标准
- 支持标准库：`<cstring>`, `<vector>`, `<stdexcept>`, `<iostream>` 等

编译示例：
```bash
g++ -std=c++11 -O2 main.cpp -o main
```
