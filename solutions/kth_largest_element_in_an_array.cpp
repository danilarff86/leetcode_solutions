#include "gtest/gtest.h"

#include <string>

using namespace std;

namespace
{
class Solution
{
public:
    int
    findKthLargest( vector< int >& nums, int k )
    {
        auto begin = 0u;
        auto end = nums.size( );
        const auto target = static_cast< size_t >( k - 1 );

        while ( begin < end )
        {
            auto last_left = begin;
            for ( auto i = begin + 1; i < end; ++i )
            {
                if ( nums[ i ] > nums[ begin ] )
                {
                    swap( nums[ ++last_left ], nums[ i ] );
                }
            }
            swap( nums[ begin ], nums[ last_left ] );

            if ( last_left > target )
            {
                end = last_left;
            }
            else if ( last_left < target )
            {
                begin = last_left + 1;
            }
            else
            {
                return nums[ last_left ];
            }
        }

        return nums[ begin ];
    }
};
}  // namespace

TEST( KthLargestElementInAnArray, generic )
{
    Solution sn;
    vector< int > nums;

    // My test
    nums = {4, 1, 2, 5, 3, 7};
    EXPECT_EQ( 5, sn.findKthLargest( nums, 2 ) );

    nums = {3, 2, 1, 5, 6, 4};
    EXPECT_EQ( 5, sn.findKthLargest( nums, 2 ) );

    nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    EXPECT_EQ( 4, sn.findKthLargest( nums, 4 ) );
}
