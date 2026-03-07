#include "Containers/CyclicArray.h"
#include <iostream>

using namespace std;

namespace Containers
{
    CCyclicArray::CCyclicArray(const int Capacity) : m_Capacity(Capacity),
                                                    m_Size(0),
                                                    m_Back(-1)
    {
        m_Elements.reserve(Capacity);
    }

    CCyclicArray::~CCyclicArray()
    {}

    int CCyclicArray::GetSize()
    {
        return m_Size;
    }

    void CCyclicArray::push_back(double Val)
    {
        if(m_Size < m_Capacity)
        {
            m_Elements.push_back(Val);
            m_Back = m_Size++;
        }
        else
        {
            m_Back = (m_Back + 1) % m_Capacity;
            m_Elements[m_Back] = Val;
        }
    }

    void CCyclicArray::push_front(double Val)
    {
        if(m_Size < m_Capacity)
        {
            m_Elements.push_back(0);

            copy_backward(m_Elements.begin(), m_Elements.end() - 1, 
                        m_Elements.end());

            m_Elements[0] = Val;
            m_Back = m_Size++;
        }
        else
        {
            m_Elements[m_Back--] = Val;
            if(m_Back < 0)
            m_Back = m_Size - 1;
        }
    }

    void CCyclicArray::pop_back()
    {
        if(m_Size > 0)
        {
            if(m_Back < m_Size - 1)
            copy(m_Elements.begin() + m_Back + 1, m_Elements.end(), 
                m_Elements.begin() + m_Back);

            m_Size--;
            m_Back--;

            m_Elements.pop_back();

            if(m_Back < 0)
            m_Back = m_Size - 1;
        }
    }

    void CCyclicArray::pop_front()
    {
        if(m_Size > 0)
        {
            if(m_Back != m_Size - 2)
            copy(m_Elements.begin() + ((m_Back + 2) % m_Size), m_Elements.end(), m_Elements.begin() + ((m_Back + 1) % m_Size));

            m_Elements.pop_back();
            m_Size--;

            if(m_Back == m_Size)
            m_Back = m_Size - 1;
        }
    }

    double CCyclicArray::operator[] (int index) const
    {
        return m_Elements[(m_Back + index + 1) % m_Size];
    }

    double& CCyclicArray::operator[] (int index)
    {
        return m_Elements[(m_Back + index + 1) % m_Size];
    }

    ostream& operator<<(ostream& out, CCyclicArray& ca)
    {
        out << "(";
        int index = 0;
        if(index < ca.m_Size) 
        {
            out << ca[index++];
            while(index < ca.m_Size)
            out << ", " << ca[index++];
        }
        out << ")";

        return out;
    }
}
