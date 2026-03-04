#include <iostream>
#include <vector>

namespace MyStaticLib3
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
            std::ostream& Out, 
            int Style = 0, 
            int Width =  3,
            int Precision = 1);        

    private:
        std::vector<double> m_Elements;
    };
}