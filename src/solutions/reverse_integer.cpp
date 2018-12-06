#include <cmath>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
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

TEST( ReverseInteger, generic )
{
    Solution sn;
    EXPECT_EQ( 321, sn.reverse( 123 ) );
    EXPECT_EQ( -321, sn.reverse( -123 ) );
    EXPECT_EQ( 21, sn.reverse( 120 ) );
    EXPECT_EQ( 0, sn.reverse( 1000000003 ) );
    EXPECT_EQ( 2147483641, sn.reverse( 1463847412 ) );
}
