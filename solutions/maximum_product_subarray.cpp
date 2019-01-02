#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxProduct( const vector< int >& nums )
    {
        int max_ending_here = nums[ 0 ], min_ending_here = nums[ 0 ], max_so_far = nums[ 0 ];
        for ( size_t i = 1; i < nums.size( ); ++i )
        {
            const auto min_mul = min_ending_here * nums[ i ];
            const auto max_mul = max_ending_here * nums[ i ];

            const auto ending_max = max( min_mul, max_mul );
            const auto ending_min = min( min_mul, max_mul );

            max_ending_here = max( ending_max, nums[ i ] );
            min_ending_here = min( ending_min, nums[ i ] );

            max_so_far = max( max_so_far, max_ending_here );
        }
        return max_so_far;
    }
};
}  // namespace

TEST( MaximumProductSubarray, generic )
{
    Solution sn;
    EXPECT_EQ( 6, sn.maxProduct( {2, 3, -2, 4} ) );
    EXPECT_EQ( 0, sn.maxProduct( {-2, 0, -1} ) );
    EXPECT_EQ( 108, sn.maxProduct( {-1, -2, -9, -6} ) );
    EXPECT_EQ( 2, sn.maxProduct( {0, 2} ) );
}
