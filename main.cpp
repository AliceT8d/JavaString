#include "JavaString.hpp"
#include <iostream>
using JavaString::Jstring;

int main()
{
    Jstring js = "Hello", js2 = "Jstring";
    std::cout << (js + ", " + js2) << std::endl;
}
