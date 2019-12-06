#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxSubArray( const vector< int >& nums )
    {
        int max_ending_here = nums[ 0 ], max_so_far = nums[ 0 ];
        for ( size_t i = 1; i < nums.size( ); ++i )
        {
            max_ending_here = max( max_ending_here + nums[ i ], nums[ i ] );
            max_so_far = max( max_so_far, max_ending_here );
        }
        return max_so_far;
    }
};
}  // namespace

TEST( MaximumSubarray, generic )
{
    Solution sn;
    EXPECT_EQ( 6, sn.maxSubArray( {-2, 1, -3, 4, -1, 2, 1, -5, 4} ) );
}
