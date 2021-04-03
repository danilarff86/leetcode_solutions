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

        vector< vector< int > > dp( SZ + 1, vector< int >( SZ + 1 ) );
        for ( size_t len = 1; len <= SZ; ++len )
        {
            for ( size_t i = 0; i <= SZ - len; ++i )
            {
                const size_t j = i + len - 1;
                const auto left_right_points = nums_with_padding[ i ] * nums_with_padding[ j + 2 ];
                auto& target = dp[ i ][ j + 1 ];
                for ( size_t k = i; k <= j; ++k )
                {
                    const auto dp_left = dp[ i ][ k ];
                    const auto dp_right = dp[ k + 1 ][ j + 1 ];
                    const auto burst_points = left_right_points * nums_with_padding[ k + 1 ];
                    auto case_val = dp_left + burst_points + dp_right;
                    if ( case_val > target )
                    {
                        target = case_val;
                    }
                }
            }
        }

        return dp[ 0 ][ SZ ];
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
