#include "JavaString.hpp"
#include <iostream>
using JavaString::Jstring;

int main()
{
    Jstring js = "aaaaaaaaaaaa", js2 = "Jstring";
    Jstring js3 = js.substring(0, 1);
    std::cout << js.toUpperCase() << std::endl;
    std::cout << js << std::endl;
}
