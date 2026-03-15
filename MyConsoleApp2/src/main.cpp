#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
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

// Dette projekt linker til de 2 hjemmelavede static link libraries: MyStaticLib3 og Containers
// Det udgør reelt også en simpel testapplikation for Containers libraryet

using namespace std;

ostream& appendRectangleToSVGRepresentation(
    ostream& out,
    Containers::CRectangle* pP,
    string fill = "black")
{
    out << "  <rect";
    out << " width=\"" << pP->GetHalfWidth() * 2 << "\"";
    out << " height=\"" << pP->GetHalfHeight() * 2  << "\"";
    out << " x=\"" << pP->GetCenterX() - pP->GetHalfWidth() << "\"";
    out << " y=\"" << pP->GetCenterY() - pP->GetHalfHeight() << "\"";

    if (fill != "black")
    {
        string fillLine = " fill=\"";
        fillLine += fill;
        fillLine += "\"";
        out << fillLine;
    }

    out << " />" << endl;

    return out;
}

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
}

void heap_test(bool waitForKey)
{
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

void bintree_test(bool waitForKey)
{
    Containers::CBinTree BinTree1, BinTree2;
    double Value;
    int i, n = 1000000;

    cout << "\nBINTREE TEST:\n" << endl;

    cout << "Inserting 10 doubles into BinTree1.." << endl;
    Continue(waitForKey);

    BinTree1.Insert(7.2);
    BinTree1.Insert(4.1);
    BinTree1.Insert(8.3);
    BinTree1.Insert(5.9);
    BinTree1.Insert(3.0);
    BinTree1.Insert(0.2);
    BinTree1.Insert(9.2);
    BinTree1.Insert(7.2);
    BinTree1.Insert(8.0);
    BinTree1.Insert(4.5);

    cout << "BinTree1:" << endl;
    BinTree1.Display(cout);
    cout << endl;

    if(BinTree1.Empty())  cout << "BinTree1 is empty" << endl;
    else                  cout << "BinTree1 is non-empty" << endl;

    Value = 5.9;
    if(BinTree1.Holds(Value))  cout << "BinTree1 holds " << Value << endl;
    else                       cout << "BinTree1 does not hold " << Value << endl;

    Value = 7.1;
    if(BinTree1.Holds(Value))  cout << "BinTree1 holds " << Value << endl;
    else                       cout << "BinTree1 does not hold " << Value << endl;

    cout << "The minimum of BinTree1 is " << BinTree1.Minimum() << endl;
    cout << "The maximum of BinTree1 is " << BinTree1.Maximum() << "\n" << endl;

    cout << "Deleting elements 5.9, 0.2, 7.2, 8.0 and 9.2" << endl;
    Continue(waitForKey);

    BinTree1.Delete(5.9);
    BinTree1.Delete(0.2);
    BinTree1.Delete(7.2);
    BinTree1.Delete(8.0);
    BinTree1.Delete(9.2);
    
    cout << "BinTree1:" << endl;
    BinTree1.Display(cout);
    cout << endl;

    cout << "Processing time required for building BinTree of " << n
         << "\n randomly generated doubles" << endl;
    Continue(waitForKey);
    auto start = std::chrono::steady_clock::now();
    srand((unsigned) time(NULL));

    for(i = 0; i < n; i++)
    {
      Value = rand();
      BinTree2.Insert(Value);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for Building bintree (homemade): " << duration.count() << " ms\n";
}

void cyclicarray_test(bool waitForKey)
{
    Containers::CCyclicArray CyclicArray1(8);
    Containers::CCyclicArray CyclicArray2(18);
    deque<double> Deque1;
    int i, N = 100000;

    cout << "\nCYCLIC-ARRAY TEST:\n" << endl;

    cout << "Pushing elements at the back.." << endl;
    cout << "  CyclicArray1: " << CyclicArray1 << endl;
    
    for(i = 1; i <= 12; i++)
    {
        CyclicArray1.push_back(i);
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Popping elements from the back.." << endl;
    for(i = 0; i < 6; i++)
    {
        CyclicArray1.pop_back();
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Pushing elements at the back.." << endl;
    for(i = 7; i <= 8; i++)
    {
        CyclicArray1.push_back(i);
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Pushing elements at the front.." << endl;
    for(i = 9; i < 21; i++)
    {
        CyclicArray1.push_front(i);
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Popping elements from the front.." << endl;
    for(i = 0; i < 6; i++)
    {
        CyclicArray1.pop_front();
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Pushing elements at the front.." << endl;
    for(i = 20; i <= 21; i++)
    {
        CyclicArray1.push_front(i);
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Pushing elements at the back.." << endl;
    for(i = 22; i <= 23; i++)
    {
        CyclicArray1.push_back(i);
        cout << "  CyclicArray1: " << CyclicArray1 << endl;
    }

    Continue(waitForKey);

    cout << "Comparing processing times for pushing " << N
        << "\nnumbers at the back of CyclicArray2\n" << endl;

    auto start = std::chrono::steady_clock::now();

    for(i = 0; i < N; i++)
    {
        CyclicArray2.push_back(3.0);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "CyclicArray: " << duration.count() << " ms\n";

    for(i = 0; i < 18; i++)
        Deque1.push_back(3);

    start = std::chrono::steady_clock::now();

    for(i = 0; i < N; i++)
    {
        Deque1.push_back(3);
        Deque1.pop_front();
    }

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Deque: " << duration.count() << " ms\n";
}

void mxcifquadtree_test(bool waitForKey)
{
    double squareSize = 10.0;
    int i, N = 10000;
    int nNonIntersecting;

    Containers::CRectangle EntireArea(50.0, 50.0, 50.0, 50.0);

    Containers::CRectangle Rectangle1(12.5, 25, 5, 5);
    Containers::CRectangle Rectangle2(50, 6.25, 1, 1);
    Containers::CRectangle Rectangle3(53.125, 12.5, 2.0, 2.0);
    Containers::CRectangle Rectangle4(62.5, 12.5, 3.0, 3.0);
    Containers::CRectangle Rectangle5(71.875, 12.5, 2.0, 2.0);
    Containers::CRectangle Rectangle6(50.0, 37.5, 3.0, 3.0);
    Containers::CRectangle Rectangle7(18.75, 50.0, 3.0, 3.0);
    Containers::CRectangle Rectangle8(50.0, 50.0, 5.0, 5.0);
    Containers::CRectangle Rectangle9(75.0, 50.0, 5.0, 5.0);
    Containers::CRectangle Rectangle10(50.0, 75.0, 5.0, 5.0);
    Containers::CRectangle Rectangle11(75.0, 75.0, 5.0, 5.0);
    Containers::CRectangle Rectangle12(87.5, 93.75, 2.0, 2.0);
    Containers::CRectangle RectangleQ(50.0, 75.0, 5.0, 5.0);

    list<Containers::CRectangle> Rectangles;
    list<Containers::CRectangle>::iterator it;

    ofstream logFile1("log1.txt");

    Containers::CMxCifQuadTree MxCifQuadTree1(EntireArea, &logFile1);
    Containers::CMxCifQuadTree MxCifQuadTree2(EntireArea, NULL);

    ofstream logFile3("log3.txt");

    Containers::CMxCifQuadTree MxCifQuadTree3(EntireArea, &logFile3);

    cout << "\nMX-CIF QUADTREE TEST:\n" << endl;

    cout << "Inserting a small number of rectangles in MxCifQuadTree1.." << endl; 
    Continue(waitForKey);

    MxCifQuadTree1.Insert(&Rectangle1);  
    MxCifQuadTree1.Insert(&Rectangle2); 
    MxCifQuadTree1.Insert(&Rectangle3); 
    MxCifQuadTree1.Insert(&Rectangle4); 
    MxCifQuadTree1.Insert(&Rectangle5); 
    MxCifQuadTree1.Insert(&Rectangle6);  
    MxCifQuadTree1.Insert(&Rectangle7);
    MxCifQuadTree1.Insert(&Rectangle8);  
    MxCifQuadTree1.Insert(&Rectangle9);  
    MxCifQuadTree1.Insert(&Rectangle10);  
    MxCifQuadTree1.Insert(&Rectangle11);  
    MxCifQuadTree1.Insert(&Rectangle12);

    // if(MxCifQuadTree1.IntersectsAny(&RectangleQ))
    //   cout << "RectangleQ intersects a number of rectangles in MxCifQuadTree1\n" << endl; 
    // else
    //   cout << "RectangleQ does not intersect any rectangles in MxCifQuadTree1\n" << endl; 

    cout << "Removing all rectangles from MxCifQuadTree1.." << endl;
    Continue(waitForKey);

    MxCifQuadTree1.Remove(&Rectangle1);
    MxCifQuadTree1.Remove(&Rectangle2);
    MxCifQuadTree1.Remove(&Rectangle3);
    MxCifQuadTree1.Remove(&Rectangle4);
    MxCifQuadTree1.Remove(&Rectangle5);
    MxCifQuadTree1.Remove(&Rectangle6);
    MxCifQuadTree1.Remove(&Rectangle7);
    MxCifQuadTree1.Remove(&Rectangle8);
    MxCifQuadTree1.Remove(&Rectangle9);
    MxCifQuadTree1.Remove(&Rectangle10);
    MxCifQuadTree1.Remove(&Rectangle11);
    MxCifQuadTree1.Remove(&Rectangle12);

    list<Containers::CRectangle*> dummy1;
    MxCifQuadTree1.GetAllIntersecting(&EntireArea, dummy1);
    cout << "Rectangles currently in MxCifQuadTree1: " << dummy1.size() << endl;

    cout << "Clearing the rest of the rectangles from MxCifQuadTree1.." << endl;
    Continue(waitForKey);

    MxCifQuadTree1.Clear();

    list<Containers::CRectangle*> dummy2;
    MxCifQuadTree1.GetAllIntersecting(&EntireArea, dummy2);
    cout << "Rectangles currently in MxCifQuadTree1: " << dummy2.size() << endl;

    cout << "Generating " << N << " randomly positioned squares of size " 
         << squareSize << "x" << squareSize << ".." << endl;

    //srand((unsigned) time(NULL)); // seeded with time => random numbers
    srand(0); // seeded with 0 => pseudo random numbers

    for(i = 0; i < N; i++)
    {
        double Frac_x = ((double)rand()) / RAND_MAX;
        double Frac_y = ((double)rand()) / RAND_MAX;

        double Center_x = Frac_x * (100 - squareSize) + 0.5 * squareSize;
        double Center_y = Frac_y * (100 - squareSize) + 0.5 * squareSize;

        // Round to integer, in order to ease debugging
        Center_x = round(Center_x);
        Center_y = round(Center_y);

        if(false)
            cout << "(" << setiosflags(ios::fixed) << setprecision(2) << Center_x << ", " 
                << setiosflags(ios::fixed) << setprecision(2) << Center_y << ")" << endl;

        Rectangles.push_back(Containers::CRectangle(Center_x, Center_y, squareSize * 0.5, squareSize * 0.5));
    }

    cout << "\nAdding the " << N << " squares to MxCifQuadTree2" << endl; 
    Continue(waitForKey);
    auto start = std::chrono::steady_clock::now();
    for(it = Rectangles.begin(); it != Rectangles.end(); it++)
        MxCifQuadTree2.Insert(&(*it));

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for Building mxcif quad tree (homemade): " << duration.count() << " ms\n";

    cout << "\nRemoving the same " << N << " squares from MxCifQuadTree2 one at a time" << endl; 
    Continue(waitForKey);

    start = std::chrono::steady_clock::now();
    for(it = Rectangles.begin(); it != Rectangles.end(); it++)
        MxCifQuadTree2.Remove(&(*it));
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for deleting rectangles: " << duration.count() << " ms\n";

    cout << "\nAdding the same " << N << " squares to MxCifQuadTree3" << endl; 
    cout << "(but rejecting intersections this time)" << endl; 
    Continue(waitForKey);

    ofstream geometryFile("mxcifquadtree3.svg");
    ofstream logFile("mxcifquadtree3_log.txt");
    ofstream allRectanglesFile("all_rectangles.txt");

    geometryFile << "<svg width=\"" << 100 << "\" height=\"" << 100  << "\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    appendRectangleToSVGRepresentation(geometryFile, &EntireArea, "gray");

    Containers::CRectangle AreaOfInterest(60.0, 40.0, 20.0, 20.0);
    //Containers::CRectangle AreaOfInterest(50.0, 50.0, 50.0, 50.0);
    appendRectangleToSVGRepresentation(geometryFile, &AreaOfInterest, "black");

    nNonIntersecting = 0;
    start = std::chrono::steady_clock::now();
    auto count = 0;

    for(it = Rectangles.begin(); it != Rectangles.end(); it++)
    {
        auto centerX = it->GetCenterX();
        auto centerY = it->GetCenterY();
        auto halfWidth = it->GetHalfWidth();
        auto halfHeight = it->GetHalfHeight();

        allRectanglesFile << centerX << ", " << centerY << ", " << halfWidth << ", " << halfHeight;

        if(!MxCifQuadTree3.IntersectsAny(&(*it)))
        {
            allRectanglesFile << ", 1"; // (accepted, i.e. not intersectiong)

            MxCifQuadTree3.Insert(&(*it));
            nNonIntersecting++;

            logFile << "Inserting " << squareSize << "x" << squareSize << " rectangle with center (x, y) = (";
            logFile << centerX << ", " << centerY << ")" << endl;

            appendRectangleToSVGRepresentation(geometryFile, &(*it), "blue");
            //break;
        }
        else
        {
            allRectanglesFile << ", 0"; // (rejected due to intersection)

            logFile << "  Rejecting " << squareSize << "x" << squareSize << " rectangle with center (x, y) = (";
            logFile << centerX << ", " << centerY << ")" << endl;
        }

        allRectanglesFile << endl;

        count++;
    }
    
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed time for rejecting intersections: " << duration.count() << " ms\n";

    // Now MxCifQuadTree3 contains a number of non intersection rectangles
    // Here, we want to get the rectangles that intersect the area of interest (defined earlier in order to render it)
    list<Containers::CRectangle*> intersectingRectangles;
    MxCifQuadTree3.GetAllIntersecting(&AreaOfInterest, intersectingRectangles);

    list<Containers::CRectangle*>::iterator it2;
    for(it2 = intersectingRectangles.begin(); it2 != intersectingRectangles.end(); it2++)
    {
        appendRectangleToSVGRepresentation(geometryFile, *it2, "yellow");
    }

    geometryFile << "</svg>" << endl;
    geometryFile.close();
    logFile.close();
    allRectanglesFile.close();
}

int main()
{
    auto waitForKey = false;

    //do_various_tests();
    //heap_test(waitForKey);
    //bintree_test(waitForKey);
    //cyclicarray_test(waitForKey);
    mxcifquadtree_test(waitForKey);
    
    return 0;
}