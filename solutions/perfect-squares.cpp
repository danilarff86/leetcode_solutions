#include <algorithm>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    numSquares( int n )
    {
        vector< int > dp( n + 1, n );
        vector< int > squares( n + 1 );
        int x = 0;
        int xx = 0;
        while ( xx <= n )
        {
            dp[ xx ] = 1;
            ++x;
            const auto xx_next = x * x;
            fill( &squares[ xx ], &squares[ min( xx_next, n ) + 1 ], xx );
            xx = xx_next;
        }
        dp[ 0 ] = 0;

        for ( int i = 0; i <= n; i++ )
        {
            xx = squares[ i ];
            while ( xx > 0 )
            {
                dp[ i ] = min( dp[ i ], dp[ i - xx ] + 1 );
                xx = squares[ xx - 1 ];
            }
        }
        return dp[ n ];
    }
};
}  // namespace

TEST( PerfectSquares, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.numSquares( 12 ) );
    EXPECT_EQ( 2, sn.numSquares( 13 ) );
}
