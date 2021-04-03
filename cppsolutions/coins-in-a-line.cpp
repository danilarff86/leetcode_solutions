#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxMoney( const vector< int >& coins )
    {
        static const int MAX_N = 100;
        int dp[ MAX_N ][ MAX_N ] = {};
        const int coins_sz = coins.size( );
        for ( auto i = 0; i < coins_sz; ++i )
        {
            for ( int a_i = 0, a_j = i; a_j < coins_sz; ++a_i, ++a_j )
            {
                const auto p_ai_plus2 = ( a_i + 2 < coins_sz ) ? dp[ a_i + 2 ][ a_j ] : 0;
                const auto p_ai_plus1_aj_minus1
                    = ( a_i + 1 < coins_sz && a_j > 0 ) ? dp[ a_i + 1 ][ a_j - 1 ] : 0;
                const auto p_ai_minus2 = ( a_j - 1 > 0 ) ? dp[ a_i ][ a_j - 2 ] : 0;
                dp[ a_i ][ a_j ] = max( coins[ a_i ] + min( p_ai_plus2, p_ai_plus1_aj_minus1 ),
                                        coins[ a_j ] + min( p_ai_plus1_aj_minus1, p_ai_minus2 ) );
            }
        }
        return dp[ 0 ][ coins_sz - 1 ];
    }
};
}  // namespace

TEST( CoinsInALine, generic )
{
    Solution sn;
    EXPECT_EQ( 8, sn.maxMoney( {3, 2, 2, 3, 1, 2} ) );
}
