#pragma once

namespace MyStaticLib
{
    int add(int a, int b);

    class Calculator
    {
    public:
        // Constructor
        Calculator();

        // Public methods
        int Add(int a, int b) const;
        int Subtract(int a, int b) const;
        int Multiply(int a, int b) const;
        double Divide(double a, double b) const;

    private:
        // Private member variable
        int _operationCount;
    };
}