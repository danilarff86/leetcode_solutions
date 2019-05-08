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
        s_end = s.data( ) + s.length( );
        p_end = p.data( ) + p.length( );
        return is_match( s.data( ), p.data( ) );
    }

private:
    bool
    is_match( const char* s, const char* p )
    {
        if ( p >= p_end )
        {
            return s >= s_end;
        }
        const auto first_match = ( s < s_end && ( p[ 0 ] == s[ 0 ] || p[ 0 ] == '.' ) );
        if ( ( p_end - p ) >= 2 && p[ 1 ] == '*' )
        {
            return ( is_match( s, p + 2 ) || ( first_match && is_match( s + 1, p ) ) );
        }
        else
        {
            return first_match && is_match( s + 1, p + 1 );
        }
    }

private:
    const char* s_end;
    const char* p_end;
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
