#include <string>
#include <vector>

#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxCoins( const vector< int >& nums )
    {
        const auto SZ = nums.size( );
        vector< int > nums_with_padding( SZ + 2 );
        nums_with_padding[ 0 ] = nums_with_padding[ SZ + 1 ] = 1;
        for ( int i = 0; i < nums.size( ); i++ )
        {
            nums_with_padding[ i + 1 ] = nums[ i ];
        }

        vector< vector< int > > dp( SZ, vector< int >( SZ ) );
        for ( size_t len = 1; len <= SZ; ++len )
        {
            for ( size_t i = 0; i <= SZ - len; ++i )
            {
                const size_t j = i + len - 1;
                for ( size_t k = i; k <= j; ++k )
                {
                    auto val = nums_with_padding[ i ] * nums_with_padding[ k + 1 ]
                               * nums_with_padding[ j + 2 ];
                    if ( k > i )
                    {
                        val += dp[ i ][ k - 1 ];
                    }
                    if ( k < j )
                    {
                        val += dp[ k + 1 ][ j ];
                    }
                    if ( val > dp[ i ][ j ] )
                    {
                        dp[ i ][ j ] = val;
                    }
                }
            }
        }

        return SZ > 0 ? dp[ 0 ][ SZ - 1 ] : 0;
    }
};
}  // namespace

TEST( BurstBalloons, generic )
{
    Solution sn;
    EXPECT_EQ( 167, sn.maxCoins( {3, 1, 5, 8} ) );
    EXPECT_EQ( 1849648, sn.maxCoins( {35, 16, 83, 87, 84, 59, 48, 41, 20, 54} ) );
    EXPECT_EQ( 0, sn.maxCoins( {} ) );
}
