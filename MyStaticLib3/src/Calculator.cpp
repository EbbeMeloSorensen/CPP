#include "MyStaticLib3/Calculator.h"
#include <stdexcept>

namespace MyStaticLib3
{
    Calculator::Calculator()
        : _operationCount(0)
    {
    }

    int Calculator::Add(int a, int b) const
    {
        return a + b;
    }

    int Calculator::Subtract(int a, int b) const
    {
        return a - b;
    }

    int Calculator::Multiply(int a, int b) const
    {
        return a * b;
    }

    double Calculator::Divide(double a, double b) const
    {
        if (b == 0.0)
        {
            throw std::invalid_argument("Division by zero");
        }

        return a / b;
    }
}