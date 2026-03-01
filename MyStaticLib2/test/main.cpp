#include <iostream>
#include "MyStaticLib/math_utils.h"

int main()
{
    std::cout << "2 + 3 = "
              << MyStaticLib::add(2, 3)
              << std::endl;

    return 0;
}