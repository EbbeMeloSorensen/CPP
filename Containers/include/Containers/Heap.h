#include <iostream>
#include <vector>

namespace Containers
{
    class CDoubleHeap
    {
    public:
        CDoubleHeap();
        ~CDoubleHeap();

        int GetSize() const;
        int GetHeight() const;
    
        double  operator [] (int index) const;
        double& operator [] (int index);

        void Append(double X);
        void Insert(double X);
        void Clear();

        void Heapify(int index);
        void Shuffle();
        void BuildHeap();

        void IncreaseKey(int index);
        void DismissPrimary();

        std::ostream& Display(
            std::ostream& out, 
            int style = 0, 
            int width =  3,
            int precision = 1);        

    private:
        std::vector<double> m_Elements;
    };
}