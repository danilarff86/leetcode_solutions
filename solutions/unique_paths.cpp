#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    uniquePaths( int m, int n )
    {
        vector< int > dp( m, 1 );
        for ( int i = 1; i < n; ++i )
        {
            for ( int j = 1; j < m; ++j )
            {
                dp[ j ] += dp[ j - 1 ];
            }
        }
        return dp[ m - 1 ];
    }
};
}  // namespace

TEST( UniquePaths, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.uniquePaths( 3, 2 ) );
    EXPECT_EQ( 28, sn.uniquePaths( 7, 3 ) );
}
