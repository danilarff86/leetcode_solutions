#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isPalindrome( string s )
    {
        auto p1 = s.c_str( );
        auto p2 = p1 + s.length( );
        while ( p1 < p2 )
        {
            while ( p1 < p2 && !isalnum( *p1 ) )
            {
                ++p1;
            }
            while ( p2 > p1 && !isalnum( *p2 ) )
            {
                --p2;
            }
            if ( tolower( *p1++ ) != tolower( *p2-- ) )
            {
                return false;
            }
        }
        return true;
    }
};
}  // namespace

TEST( ValidPalindrome, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isPalindrome( "A man, a plan, a canal: Panama" ) );
    EXPECT_FALSE( sn.isPalindrome( "race a car" ) );
}