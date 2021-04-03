#include "gtest/gtest.h"

#include <climits>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    minCut( string s )
    {
        vector< vector< bool > > is_palindrome_dp( s.size( ), vector< bool >( s.size( ) ) );
        for ( int r = 0; r < s.size( ); ++r )
        {
            is_palindrome_dp[ r ][ r ] = true;
            if ( r > 0 )
            {
                is_palindrome_dp[ r - 1 ][ r ] = s[ r - 1 ] == s[ r ];
            }

            for ( int l = r - 2; l >= 0; --l )
            {
                is_palindrome_dp[ l ][ r ]
                    = ( s[ l ] == s[ r ] ) && is_palindrome_dp[ l + 1 ][ r - 1 ];
            }
        }

        vector< int > dp( s.size( ) + 1, numeric_limits< int >::max( ) );
        dp[ 0 ] = -1;
        for ( int r = 0; r < s.length( ); ++r )
        {
            for ( int l = r; l >= 0; --l )
            {
                if ( is_palindrome_dp[ l ][ r ] )
                {
                    dp[ r + 1 ] = min( dp[ r + 1 ], dp[ l ] + 1 );
                }
            }
        }

        return dp.back( );
    }
};
}  // namespace

TEST( PalindromePartitioningII, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.minCut( "aab" ) );
    EXPECT_EQ( 1, sn.minCut( "abb" ) );
}
