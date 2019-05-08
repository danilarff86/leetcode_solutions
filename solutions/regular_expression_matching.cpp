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
        if ( p.empty( ) )
        {
            return s.empty( );
        }
        const auto first_match = ( !s.empty( ) && ( p[ 0 ] == s[ 0 ] || p[ 0 ] == '.' ) );

        if ( p.length( ) >= 2 && p[ 1 ] == '*' )
        {
            return ( isMatch( s, p.substr( 2 ) )
                     || ( first_match && isMatch( s.substr( 1 ), p ) ) );
        }
        else
        {
            return first_match && isMatch( s.substr( 1 ), p.substr( 1 ) );
        }
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
}
