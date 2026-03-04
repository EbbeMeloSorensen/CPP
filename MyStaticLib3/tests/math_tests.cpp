#include <gtest/gtest.h>
#include "MyStaticLib/Heap.h"

using namespace MyStaticLib;

TEST(AddiwwtionTests, AddsPosiwwtiveNumbers)
{
    CDoubleHeap heap1;
    int size = heap1.GetSize();
    
    EXPECT_EQ(0, size);
}

