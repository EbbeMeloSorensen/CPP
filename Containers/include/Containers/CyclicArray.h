#include <vector>
#include <iostream>

namespace Containers
{
    class CCyclicArray
    {
    public:
        CCyclicArray(const int Capacity);
        ~CCyclicArray();

        int GetSize();

        void push_back (double Val);
        void push_front(double Val);

        void pop_back();
        void pop_front();

        double  operator[](int Index) const;
        double& operator[](int Index);

    private:
        std::vector<double>  m_Elements;
        int                  m_Capacity;
        int                  m_Size;
        int                  m_Back;

    friend std::ostream& operator<<(std::ostream& out, CCyclicArray& ca);
    };
}