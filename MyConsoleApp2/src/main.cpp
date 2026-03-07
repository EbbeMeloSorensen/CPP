#include <iostream>
#include <MyStaticLib3/Calculator.h>
#include <Containers/Heap.h>
#include <Containers/BinTree.h>

// Dette projekt linker til de 2 hjemmelavede static link libraries vist ovenfor

int main()
{
    MyStaticLib3::Calculator calc;
    std::cout << "2 + 3 = " << calc.Add(2, 3) << std::endl;

    Containers::CDoubleHeap heap1;
    heap1.Append(9.0);
    heap1.Append(13.0);
    heap1.Append(7.0);

    std::cout << "Heap size = " << heap1.GetSize() << std::endl;

    std::cout << "My Heap:" << std::endl;
    heap1.Display(std::cout, 1);

    heap1.DismissPrimary();

    std::cout << heap1[0] << std::endl;

    Containers::CBinTree binTree1;
    binTree1.Insert(9.0);
    binTree1.Insert(13.0);
    binTree1.Insert(7.0);

    std::cout << "My BinTree:" << std::endl;
    binTree1.Display(std::cout);
    
    return 0;
}