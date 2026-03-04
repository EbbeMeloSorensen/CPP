#include <gtest/gtest.h>
#include "MyStaticLib2/math_utils.h"

TEST(AdditionTests, AddsPositiveNumbers)
{
    EXPECT_EQ(5, MyStaticLib2::add(2, 3));
}

TEST(AdditionTests, AddsNegativeNumbers)
{
    EXPECT_EQ(-5, MyStaticLib2::add(-2, -3));
}

TEST(AdditionTests, MixedSigns)
{
    EXPECT_EQ(1, MyStaticLib2::add(3, -2));
}