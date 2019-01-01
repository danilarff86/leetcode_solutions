#include "gtest/gtest.h"

#include <stack>
#include <unordered_map>

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isValid( string s )
    {
        static const unordered_map< char, char > parentheses_mapping
            = {{')', '('}, {'}', '{'}, {']', '['}};
        stack< char > working_mem;
        for ( const auto c : s )
        {
            auto c_it = parentheses_mapping.find( c );
            if ( c_it != parentheses_mapping.end( ) )
            {
                if ( working_mem.empty( ) || c_it->second != working_mem.top( ) )
                {
                    return false;
                }
                working_mem.pop( );
            }
            else
            {
                working_mem.push( c );
            }
        }
        return working_mem.empty( );
    }
};
}  // namespace

TEST( ValidParentheses, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isValid( "()" ) );
    EXPECT_TRUE( sn.isValid( "()[]{}" ) );
    EXPECT_FALSE( sn.isValid( "(]" ) );
    EXPECT_FALSE( sn.isValid( "([)]" ) );
    EXPECT_TRUE( sn.isValid( "{[]}" ) );
    EXPECT_FALSE( sn.isValid( "]" ) );
}
