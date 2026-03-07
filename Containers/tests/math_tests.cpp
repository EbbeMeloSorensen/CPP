#include <gtest/gtest.h>
#include "Containers/Heap.h"

using namespace Containers;

TEST(AddiwwtionTests, AddsPosiwwtiveNumbers)
{
    CDoubleHeap heap1;
    int size = heap1.GetSize();
    
    EXPECT_EQ(0, size);
}

