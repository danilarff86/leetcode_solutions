#include <algorithm>
#include <stack>
#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace dp_approach
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
}  // namespace dp_approach

namespace stack_approach
{
class Solution
{
public:
    int
    longestValidParentheses( string s )
    {
        int res = 0;
        stack< int > stk;

        stk.push( -1 );

        for ( size_t i = 0; i < s.size( ); i++ )
        {
            if ( s[ i ] == '(' )
            {
                stk.push( i );
            }
            else
            {
                stk.pop( );
                if ( stk.empty( ) )
                {
                    stk.push( i );
                }
                else
                {
                    const auto len = i - stk.top( );
                    if ( len > res )
                    {
                        res = len;
                    }
                }
            }
        }

        return res;
    }
};
}  // namespace stack_approach

TEST( LongestValidParentheses, generic )
{
    dp_approach::Solution sn_dp;
    EXPECT_EQ( 2, sn_dp.longestValidParentheses( "(()" ) );
    EXPECT_EQ( 4, sn_dp.longestValidParentheses( ")()())" ) );
    EXPECT_EQ( 6, sn_dp.longestValidParentheses( "(()())" ) );
    EXPECT_EQ( 68,
               sn_dp.longestValidParentheses(
                   "(()()(()(()))()((()))((()(()())()(()))())))()(()()))())))))))()()()()))(((()"
                   "())((()()(((())))()(()()(())((()))))))(()(()))(((()())()))(()))((((()(()()()"
                   "())()()(()))(()()(())()((()()())))(())()())()(" ) );

    stack_approach::Solution sn_stack;
    EXPECT_EQ( 2, sn_stack.longestValidParentheses( "(()" ) );
    EXPECT_EQ( 4, sn_stack.longestValidParentheses( ")()())" ) );
    EXPECT_EQ( 6, sn_stack.longestValidParentheses( "(()())" ) );
    EXPECT_EQ( 68,
               sn_stack.longestValidParentheses(
                   "(()()(()(()))()((()))((()(()())()(()))())))()(()()))())))))))()()()()))(((()"
                   "())((()()(((())))()(()()(())((()))))))(()(()))(((()())()))(()))((((()(()()()"
                   "())()()(()))(()()(())()((()()())))(())()())()(" ) );
}
