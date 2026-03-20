#include <gtest/gtest.h>
#include "MyStaticLib3/Calculator.h"
#include "MyStaticLib3/Heap.h"

using namespace MyStaticLib3;

TEST(AddiwwtionTests, AddsPosiwwtiveNumbers)
{
    CDoubleHeap heap1;
    int size = heap1.GetSize();
    size = 2; // Make the test fail
    
    EXPECT_EQ(0, size);
}

