#include "gtest/gtest.h"

#include <algorithm>
#include <stack>

using namespace std;

namespace
{
class Solution_dp
{
public:
    int
    trap( vector< int >& height )
    {
        const auto count = height.size( );
        vector< int > dp_left( height.size( ) );
        vector< int > dp_right( height.size( ) );
        int max_left = 0;
        int max_right = 0;
        for ( size_t i = 0; i < count; i++ )
        {
            max_left = max( max_left, height[ i ] );
            dp_left[ i ] = max_left;

            const auto right_index = count - i - 1;
            max_right = max( max_right, height[ right_index ] );
            dp_right[ right_index ] = max_right;
        }

        int res = 0;
        for ( size_t i = 0; i < count; i++ )
        {
            res += min( dp_left[ i ], dp_right[ i ] ) - height[ i ];
        }

        return res;
    }
};

class Solution_stack
{
public:
    int
    trap( vector< int >& height )
    {
        const auto count = height.size( );
        stack< int > s;
        int max_height = 0;
        int res = 0;

        for ( size_t i = 0; i < count; i++ )
        {
            auto min_height = height[ i ];
            if ( min_height > max_height )
            {
                swap( max_height, min_height );
            }
            while ( !s.empty( ) && height[ i ] > height[ s.top( ) ] )
            {
                const auto top = s.top( );
                s.pop( );
                const auto distance = s.empty( ) ? 1 : top - s.top( );
                res += ( min_height - height[ top ] ) * distance;
            }
            s.push( i );
        }

        return res;
    }
};

class Solution
{
public:
    int
    trap( vector< int >& height )
    {
        int  left = 0;
        int right = height.size( ) - 1;
        int left_max = 0;
        int right_max = 0;
        int res = 0;

        while ( left < right )
        {
            if ( height[ left ] < height[ right ] )
            {
                if ( height[ left ] >= left_max )
                {
                    left_max = height[ left ];
                }
                else
                {
                    res += left_max - height[ left ];
                }
                ++left;
            }
            else
            {
                if ( height[ right ] >= right_max )
                {
                    right_max = height[ right ];
                }
                else
                {
                    res += right_max - height[ right ];
                }
                --right;
            }
        }

        return res;
    }
};
}  // namespace

TEST( TrappingRainWater, generic )
{
    Solution sn;
    {
        vector< int > height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        EXPECT_EQ( 6, sn.trap( height ) );
    }
    {
        vector< int > height = {4, 2, 3};
        EXPECT_EQ( 1, sn.trap( height ) );
    }
    {
        vector< int > height = {};
        EXPECT_EQ( 0, sn.trap( height ) );
    }
    {
        vector< int > height = {0, 7, 1, 4, 6};
        EXPECT_EQ( 7, sn.trap( height ) );
    }
    {
        vector< int > height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        EXPECT_EQ( 6, sn.trap( height ) );
    }
    {
        vector< int > height = {1, 7, 8};
        EXPECT_EQ( 0, sn.trap( height ) );
    }
    {
        vector< int > height = {6, 5, 2, 5, 6, 9, 1, 1};
        EXPECT_EQ( 6, sn.trap( height ) );
    }
    {
        vector< int > height = {2, 1, 2, 6, 9, 7, 5, 5, 7};
        EXPECT_EQ( 5, sn.trap( height ) );
    }
}
