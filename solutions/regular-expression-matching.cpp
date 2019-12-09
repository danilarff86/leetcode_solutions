#include "gtest/gtest.h"

#include <algorithm>
#include <string>

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isMatch( string s, string p )
    {
        vector< vector< int > > dp
            = vector< vector< int > >( s.size( ) + 1, vector< int >( p.size( ) + 1 ) );
        dp[ s.length( ) ][ p.length( ) ] = true;

        for ( int j = p.length( ) - 2; j >= 0; j-- )
        {
            if ( p[ j + 1 ] == '*' )
            {
                dp[ s.length( ) ][ j ] = dp[ s.length( ) ][ j + 2 ];
            }
            else
            {
                dp[ s.length( ) ][ j ] = false;
            }
        }

        for ( int i = s.length( ) - 1; i >= 0; i-- )
        {
            for ( int j = p.length( ) - 1; j >= 0; j-- )
            {
                const auto first_match = p[ j ] == s[ i ] || p[ j ] == '.';
                if ( j + 1 < p.length( ) && p[ j + 1 ] == '*' )
                {
                    dp[ i ][ j ] = dp[ i ][ j + 2 ] || first_match && dp[ i + 1 ][ j ];
                }
                else
                {
                    dp[ i ][ j ] = first_match && dp[ i + 1 ][ j + 1 ];
                }
            }
        }
        return dp[ 0 ][ 0 ];
    }
};
}  // namespace

TEST( RegularExpressionMatching, generic )
{
    Solution sn;
    EXPECT_FALSE( sn.isMatch( "aa", "a" ) );
    EXPECT_TRUE( sn.isMatch( "aa", "a*" ) );
    EXPECT_TRUE( sn.isMatch( "aa", ".*" ) );
    EXPECT_TRUE( sn.isMatch( "abc", "a*b*c" ) );
    EXPECT_FALSE( sn.isMatch( "mississipi", "mis*is*p*." ) );
    EXPECT_TRUE( sn.isMatch( "aaa", "b*a*" ) );
    EXPECT_FALSE( sn.isMatch( "bccbbabcaccacbcacaa", ".*b.*c*.*.*.c*a*.c" ) );
}
