#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <chrono>
#include <algorithm>
#include <random>
#include <MyStaticLib3/Calculator.h>
#include <Containers/Heap.h>
#include <Containers/BinTree.h>
#include <Containers/CyclicArray.h>
#include <Containers/MxCifQuadTree.h>

// Dette projekt linker til de 2 hjemmelavede static link libraries vist ovenfor

using namespace std;

void Continue(bool waitForKey = false)
{
    if(waitForKey)
    {
        cout << "\n(Press any key to proceed)..\n" << endl;
        _getch();
    }
    else
        cout << "\n(Computing..)\n" << endl;
}

void do_various_tests()
{
    MyStaticLib3::Calculator calc;
    cout << "2 + 3 = " << calc.Add(2, 3) << endl;

    // Fun with Heap
    Containers::CDoubleHeap heap1;
    heap1.Append(9.0);
    heap1.Append(13.0);
    heap1.Append(7.0);

    cout << "Heap size = " << heap1.GetSize() << endl;

    cout << "My Heap:" << endl;
    heap1.Display(std::cout, 1);

    heap1.DismissPrimary();

    cout << heap1[0] << endl;

    // Fun with BinTree
    Containers::CBinTree binTree1;
    binTree1.Insert(9.0);
    binTree1.Insert(13.0);
    binTree1.Insert(7.0);

    cout << "My BinTree:" << endl;
    binTree1.Display(std::cout);

    // Fun with CyclicArray
    Containers::CCyclicArray cyclicArray1(10);
    cyclicArray1.push_back(9.0);
    cyclicArray1.push_front(7.0);
    cyclicArray1.push_back(13.0);

    cout << "Size of cyclic array" << cyclicArray1.GetSize() << endl;

    // Fun with MxCifQuadTree
    Containers::CRectangle rectangle(0.0, 0.0, 10.0, 10.0);
    Containers::CMxCifQuadTree mxCifQuadTree1(rectangle);

    // Todo: insert some rectangles
    
    cout << endl << "Done :)" << endl;
}

void heap_test()
{
    bool waitForKey = false;

    vector<double> vector1;
    Containers::CDoubleHeap heap1;
    int i, n = 1000000;

    cout << "\nHEAP TEST:\n" << endl;
    cout << "Inserting 30 doubles into Heap1.." << endl;
    Continue(waitForKey);

    heap1.Insert(7.2);
    heap1.Insert(4.1);
    heap1.Insert(8.3);
    heap1.Insert(5.9);
    heap1.Insert(3.0);
    heap1.Insert(0.2);
    heap1.Insert(9.2);
    heap1.Insert(7.2);
    heap1.Insert(8.0);
    heap1.Insert(4.5);
    heap1.Insert(2.2);
    heap1.Insert(8.8);
    heap1.Insert(6.1);
    heap1.Insert(9.2);
    heap1.Insert(7.3);
    heap1.Insert(4.2);
    heap1.Insert(8.4);
    heap1.Insert(5.8);
    heap1.Insert(3.1);
    heap1.Insert(0.3);
    heap1.Insert(9.1);
    heap1.Insert(7.3);
    heap1.Insert(8.1);
    heap1.Insert(4.4);
    heap1.Insert(2.3);
    heap1.Insert(6.5);
    heap1.Insert(9.2);
    heap1.Insert(8.8);
    heap1.Insert(7.7);
    heap1.Insert(9.9);

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "heap1 holds " << heap1.GetSize() << " elements." << endl;
    cout << "heap1 has a height of " << heap1.GetHeight() << "." << endl;
    cout << "heap1[4] = " << heap1[4] << "\n" << endl;
    cout << "Altering heap1[4] to 3.1" << endl;

    Continue(waitForKey);
    heap1[4] = 3.1;
    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Invoking Heapify(4).." << endl;
    Continue(waitForKey);

    heap1.Heapify(4);

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Shuffling Heap1.." << endl;
    Continue(waitForKey);

    heap1.Shuffle();

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Building Heap1.." << endl;
    Continue(waitForKey);

    heap1.BuildHeap();

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Altering Heap1[17] to 9.6" << endl;
    Continue(waitForKey);

    heap1[17] = 9.6;

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Invoking IncreaseKey(17).." << endl;
    Continue(waitForKey);

    heap1.IncreaseKey(17);

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Invoking DismissPrimary 5 times.." << endl;
    Continue(waitForKey);

    for(i = 0; i < 5; i++)
      heap1.DismissPrimary();

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Clearing Heap1.." << endl;
    Continue(waitForKey);

    heap1.Clear();

    cout << "Heap1:" << endl;
    heap1.Display(cout, 1);
    cout << endl;

    cout << "Comparing processing times for transforming " << n
         << "\n randomly shuffled numbers into a heap" << endl;
    Continue(waitForKey);

    for(i = 0; i < n; i++)
      heap1.Append(0.1 * i);
    heap1.Shuffle();
    auto start = std::chrono::steady_clock::now();
    heap1.BuildHeap();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for BuildHeap (homemade): " << duration.count() << " ms\n";

    for(i = 0; i < n; i++)
      vector1.push_back(0.1 * i);

    random_device rd;
    mt19937 g(rd());
    shuffle(vector1.begin(), vector1.end(), g);

    start = std::chrono::steady_clock::now();
    make_heap(vector1.begin(), vector1.end());
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for make_heap (from stl - the C++ standard template library): " << duration.count() << " ms\n";
}

int main()
{
    //do_various_tests();

    heap_test();


    
    return 0;
}