#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    uniquePathsWithObstacles( const vector< vector< int > >& obstacleGrid )
    {
        const auto n = obstacleGrid.size( );
        const auto m = obstacleGrid[ 0 ].size( );
        vector< int > dp( m, 0 );
        for ( int i = 0; i < m; ++i )
        {
            if ( obstacleGrid[ 0 ][ i ] == 1 )
            {
                break;
            }
            dp[ i ] = 1;
        }
        for ( int i = 1; i < n; ++i )
        {
            dp[ 0 ] = obstacleGrid[ i ][ 0 ] == 1 ? 0 : dp[ 0 ];
            for ( int j = 1; j < m; ++j )
            {
                dp[ j ] = obstacleGrid[ i ][ j ] == 1 ? 0 : dp[ j ] + dp[ j - 1 ];
            }
        }
        return dp[ m - 1 ];
    }
};
}  // namespace

TEST( UniquePathsII, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.uniquePathsWithObstacles( {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}} ) );
}
