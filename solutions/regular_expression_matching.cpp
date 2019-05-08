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
        dp = vector< vector< int > >( s.length( ) + 1, vector< int >( p.length( ) + 1, -1 ) );
        return is_match( s.data( ), p.data( ) );
    }

private:
    bool
    is_match( const char* s, const char* p )
    {
        const auto s_len = s_end - s;
        const auto p_len = p_end - p;
        if ( dp[ s_len ][ p_len ] != -1 )
        {
            return dp[ s_len ][ p_len ];
        }

        bool answer = false;
        if ( p_len == 0 )
        {
            answer = s_len == 0;
        }
        else
        {
            const auto first_match = ( s_len > 0 && ( p[ 0 ] == s[ 0 ] || p[ 0 ] == '.' ) );
            if ( p_len >= 2 && p[ 1 ] == '*' )
            {
                answer = is_match( s, p + 2 ) || ( first_match && is_match( s + 1, p ) );
            }
            else
            {
                answer = first_match && is_match( s + 1, p + 1 );
            }
        }

        dp[ s_len ][ p_len ] = answer;
        return answer;
    }

private:
    const char* s_end;
    const char* p_end;
    vector< vector< int > > dp;
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
