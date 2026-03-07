#include <iostream>
#include <MyStaticLib3/Calculator.h>

int main()
{
    MyStaticLib3::Calculator calc;
    std::cout << "2 + 3 = " << calc.Add(2, 3) << std::endl;
    
    return 0;
}