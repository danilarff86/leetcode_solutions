#include <string>
#include <unordered_set>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< string >
    removeInvalidParentheses( const string& s )
    {
        int misplaced_left = 0;
        int misplaced_right = 0;
        for ( const auto c : s )
        {
            if ( c == '(' )
            {
                ++misplaced_left;
            }
            else if ( c == ')' )
            {
                if ( misplaced_left > 0 )
                {
                    --misplaced_left;
                }
                else
                {
                    ++misplaced_right;
                }
            }
        }

        unordered_set< string > res;
        recurse( res, s, string{}, 0, 0, misplaced_left, misplaced_right );
        return vector< string >( res.begin( ), res.end( ) );
    }

private:
    void
    recurse( unordered_set< string >& res,
             const string& orig,
             string s,
             int index,
             int validity,
             int left_cnt,
             int right_cnt )
    {
        for ( size_t i = index; i < orig.size( ) && validity >= 0; i++ )
        {
            const auto c = orig[ i ];
            switch ( c )
            {
            case '(':
            {
                if ( left_cnt > 0 )
                {
                    recurse( res, orig, s, i + 1, validity, left_cnt - 1, right_cnt );
                }
                ++validity;
                break;
            }
            case ')':
            {
                if ( right_cnt > 0 )
                {
                    recurse( res, orig, s, i + 1, validity, left_cnt, right_cnt - 1 );
                }
                --validity;
                break;
            }
            default:
            {
                break;
            }
            }
            s.push_back( c );
        }

        if ( validity == 0 )
        {
            res.insert( s );
        }
    }
};
}  // namespace

TEST( RemoveInvalidParentheses, generic )
{
    Solution sn;

    EXPECT_EQ( ( vector< string >{"()()()", "(())()"} ), sn.removeInvalidParentheses( "()())()" ) );
    EXPECT_EQ( ( vector< string >{"(a)()()", "(a())()"} ),
               sn.removeInvalidParentheses( "(a)())()" ) );
    EXPECT_EQ( ( vector< string >{""} ), sn.removeInvalidParentheses( ")(" ) );
    EXPECT_EQ( ( vector< string >{"()()"} ), sn.removeInvalidParentheses( "()))((()" ) );
}
