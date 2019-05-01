#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxArea( vector< int >& height )
    {
        int left = 0;
        int right = height.size( ) - 1;
        int max_area = 0;
        while ( left < right )
        {
            const auto left_val = height[ left ];
            const auto right_val = height[ right ];
            const auto distance = ( right - left );
            if ( left_val <= right_val )
            {
                max_area = max( max_area, distance * left_val );
                ++left;
            }
            else
            {
                max_area = max( max_area, distance * right_val );
                --right;
            }
        }
        return max_area;
    }
};
}  // namespace

TEST( ContainerWithMostWater, generic )
{
    Solution sn;
    {
        vector< int > height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        EXPECT_EQ( 49, sn.maxArea( height ) );
    }
    {
        vector< int > height = {1, 2};
        EXPECT_EQ( 1, sn.maxArea( height ) );
    }
    {
        vector< int > height = {1, 2, 4, 3};
        EXPECT_EQ( 4, sn.maxArea( height ) );
    }
}
