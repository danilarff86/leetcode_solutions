#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isMatch( string s, string p )
    {
        vector< vector< bool > > dp
            = vector< vector< bool > >( s.size( ) + 1, vector< bool >( p.size( ) + 1 ) );
        dp[ 0 ][ 0 ] = true;

        for ( size_t i = 0; i < p.size( ); i++ )
        {
            dp[ 0 ][ i + 1 ] = p[ i ] == '*' && dp[ 0 ][ i ];
        }

        for ( int i_s = 1; i_s <= s.size( ); i_s++ )
        {
            for ( int i_p = 1; i_p <= p.size( ); i_p++ )
            {
                if ( p[ i_p - 1 ] == '*' )
                {
                    dp[ i_s ][ i_p ] = dp[ i_s ][ i_p - 1 ] || dp[ i_s - 1 ][ i_p ];
                }
                else
                {
                    const auto char_match
                        = ( p[ i_p - 1 ] == s[ i_s - 1 ] ) || ( p[ i_p - 1 ] == '?' );
                    dp[ i_s ][ i_p ] = char_match && dp[ i_s - 1 ][ i_p - 1 ];
                }
            }
        }

        return dp[ s.size( ) ][ p.size( ) ];
    }
};
}  // namespace

TEST( WildcardMatching, generic )
{
    Solution sn;
    EXPECT_FALSE( sn.isMatch( "aa", "a" ) );
    EXPECT_TRUE( sn.isMatch( "aa", "*" ) );
    EXPECT_TRUE( sn.isMatch( "aaa", "a*" ) );
    EXPECT_FALSE( sn.isMatch( "cb", "?a" ) );
    EXPECT_TRUE( sn.isMatch( "adceb", "*a*b" ) );
    EXPECT_FALSE( sn.isMatch( "acdcb", "a*c?b" ) );
    EXPECT_TRUE( sn.isMatch( "abcdef", "ab*f" ) );
    EXPECT_FALSE( sn.isMatch( "aab", "c*a*b" ) );
}
