#include "gtest/gtest.h"

namespace
{
    struct Solution
    {
        bool
        solution( ) const
        {
            return false;
        }
    };
}

TEST(TwoSum, generic)
{
    EXPECT_TRUE( Solution( ).solution( ) );
}