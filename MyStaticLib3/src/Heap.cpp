#include "MyStaticLib3/Heap.h"
#include <iomanip>

using namespace std;

namespace MyStaticLib3
{
    CDoubleHeap::CDoubleHeap()
    {
        // Insert a dummy element at the front in order to have indexing 
        // effectively start at 1, thereby making possible the calculation
        // of children & parent indexes by bitshifting
        m_Elements.push_back(0.0);
    }

    CDoubleHeap::~CDoubleHeap()
    {
    }

    int CDoubleHeap::GetSize() const
    {
        return m_Elements.size() - 1; 
    }

    int CDoubleHeap::GetHeight() const
    {
        int  nElements = GetSize();
        int  Height = 1;
        int  Ceiling = 2;

        do
        {
            if(nElements < Ceiling)
            return Height;

            Height++;
            Ceiling *= 2;
            
        } while(true);
    }

    double CDoubleHeap::operator [] (int index) const
    {
        return *(m_Elements.begin() + 1 + index);
    }

    double& CDoubleHeap::operator [] (int index)
    {
        return *(m_Elements.begin() + 1 + index);
    }

    void CDoubleHeap::Append(double X)
    {
        m_Elements.push_back(X);
    }

    void CDoubleHeap::Insert(double X)
    {
        // Append the element to the heap
        Append(X);

        // Then invoke IncreaseKey
        IncreaseKey(GetSize() - 1);
    }

    void CDoubleHeap::Clear()
    {
        m_Elements.clear();
        m_Elements.push_back(0.0);
    }

    void CDoubleHeap::Heapify(int index)
    {
        vector<double>::iterator current, child, largest;
        int index_current, index_child, index_largest;
        int size = GetSize();
        bool proceed;

        index_current = index + 1;
        current = m_Elements.begin() + index_current;

        do
        {
            largest = current;
            index_largest = index_current;
            proceed = false;

            // Left child
            index_child = index_current << 1;

            if(index_child <= size)
            {
                child = m_Elements.begin() + index_child;

                if(*child > *current)
                {
                    largest = child;
                    index_largest = index_child;
                }
            }

            // Right child
            index_child = index_current << 1 | 1;

            if(index_child <= size)
            {
                child = m_Elements.begin() + index_child;

                if(*child > *largest)
                {
                    largest = child;
                    index_largest = index_child;
                }
            }

            if(current != largest)
            {
                swap(*current, *largest);
                current = largest;
                index_current = index_largest;
                proceed = true;
            }

        } while(proceed);
    }

    void CDoubleHeap::BuildHeap()
    {
        int index;

        for(index = GetSize() / 2 - 1; index >= 0; index--)
            Heapify(index);
    }

    void CDoubleHeap::IncreaseKey(int index)
    {
        vector<double>::iterator  current, parent;
        double                    X;
        int                       i;
        
        i = index + 1;
        current = m_Elements.begin() + i;
        i >>= 1;
        parent = m_Elements.begin() + i;
        X = *current;
        while(i > 0 && *parent < X)
        {
            *current = *parent;
            current = parent;
            i >>= 1;
            parent = m_Elements.begin() + i;
        }
        *current = X;
    }

    void CDoubleHeap::DismissPrimary()
    {
        *(m_Elements.begin() + 1) = m_Elements.back();
        m_Elements.pop_back();
        Heapify(0);
    }
}
