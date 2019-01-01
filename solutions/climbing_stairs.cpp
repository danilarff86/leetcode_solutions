#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    climbStairs( int n )
    {
        int p = 1, q = 1;
        for ( int i = 2; i <= n; i++ )
        {
            int temp = q;
            q += p;
            p = temp;
        }
        return q;
    }
};
}  // namespace

TEST( ClimbingStairs, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.climbStairs( 2 ) );
    EXPECT_EQ( 3, sn.climbStairs( 3 ) );
    EXPECT_EQ( 13, sn.climbStairs( 6 ) );
}
