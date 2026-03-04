#include <iostream>
#include <Math/Calculator.h>

int main()
{
    Math::Calculator calc;
    std::cout << "2 + 3 = " << calc.add(2, 3) << std::endl;

    return 0;
}