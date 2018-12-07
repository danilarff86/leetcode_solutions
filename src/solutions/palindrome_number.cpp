#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isPalindrome( int x )
    {
        return x >= 0 && x == reverse( x );
    }

private:
    int
    reverse( int x )
    {
        int res = 0;
        while ( x != 0 )
        {
            if ( abs( res ) > 214748364 )
            {
                return 0;
            }
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};
}  // namespace

TEST( PalindromeNumber, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isPalindrome( 121 ) );
    EXPECT_FALSE( sn.isPalindrome( -121 ) );
    EXPECT_FALSE( sn.isPalindrome( 10 ) );
}
