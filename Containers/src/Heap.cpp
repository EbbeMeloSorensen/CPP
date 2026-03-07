#include "Containers/Heap.h"
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

namespace Containers
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

    void CDoubleHeap::Shuffle()
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(m_Elements.begin(), m_Elements.end(), g);
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

    ostream& CDoubleHeap::Display(
        ostream& out,
        int style,
        int width,
        int precision)
    {
        vector<double>::iterator it;

        switch(style)
        {
            case 0:
            {
                it = m_Elements.begin() + 1;

                if(it != m_Elements.end())
                {
                    out << *(it++);
                    while(it != m_Elements.end())
                    out << " " << *(it++);
                }

                break;
            }
            case 1:
            {
                int i, j, Alfa;
                int ElementWidth = 3;
                int Height = GetHeight();
                int Level, Margin, Spacing;

                it = m_Elements.begin() + 1;

                for(Level = 0; Level < Height; Level++)
                {
                    Alfa = pow(2, Height - Level);
                    Margin = Alfa - (ElementWidth + 1) / 2;
                    Spacing = (Alfa / 2 - 1) * (ElementWidth + 1) + 1;

                    // Margin
                    for(i = 0; i < Margin; i++)
                    out << " ";

                    // Elements
                    i = 0;
                    while(it != m_Elements.end() && i < pow(2, Level))
                    {
                        out << setw(width) << setiosflags(ios::fixed) << setprecision(precision) << *it;

                        for(j = 0; j < Spacing; j++)
                            out << " ";

                    it++;
                    i++;
                    }

                    cerr << endl;
                }

                break;
            }
        }

        return out;
    }
}
