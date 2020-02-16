#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    longestValidParentheses( string s )
    {
        if ( s.length( ) < 2 )
        {
            return 0;
        }

        vector< int > dp( s.size( ) );

        if ( s[ 1 ] == ')' && s[ 0 ] == '(' )
        {
            dp[ 1 ] = 2;
        }

        for ( size_t i = 2; i < s.size( ); i++ )
        {
            if ( s[ i ] == ')' )
            {
                if ( s[ i - 1 ] == '(' )
                {
                    dp[ i ] += dp[ i - 2 ] + 2;
                }
                else if ( ( i - 1 >= dp[ i - 1 ] ) && s[ i - 1 - dp[ i - 1 ] ] == '(' )
                {
                    dp[ i ] += dp[ i - 1 ] + 2;
                    if ( i - 2 >= dp[ i - 1 ] )
                    {
                        dp[ i ] += dp[ i - dp[ i - 1 ] - 2 ];
                    }
                }
            }
        }

        int res = 0;
        for ( auto d : dp )
        {
            if ( d > res )
            {
                res = d;
            }
        }

        return res;
    }
};
}  // namespace

TEST( LongestValidParentheses, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.longestValidParentheses( "(()" ) );
    EXPECT_EQ( 4, sn.longestValidParentheses( ")()())" ) );
    EXPECT_EQ( 6, sn.longestValidParentheses( "(()())" ) );
    EXPECT_EQ( 68, sn.longestValidParentheses(
                      "(()()(()(()))()((()))((()(()())()(()))())))()(()()))())))))))()()()()))(((()"
                      "())((()()(((())))()(()()(())((()))))))(()(()))(((()())()))(()))((((()(()()()"
                      "())()()(()))(()()(())()((()()())))(())()())()(" ) );
}
