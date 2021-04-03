#include <queue>
#include <set>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    nthUglyNumber( int n )
    {
        int arr[ 1690 ];
        arr[ 0 ] = 1;
        int i2 = 0, i3 = 0, i5 = 0, mul2 = 2, mul3 = 3, mul5 = 5;
        for ( int i = 1; i < n; i++ )
        {
            int num = min( mul2, min( mul3, mul5 ) );
            arr[ i ] = num;
            if ( num == mul2 )
            {
                i2++;
                mul2 = arr[ i2 ] * 2;
            }
            if ( num == mul3 )
            {
                i3++;
                mul3 = arr[ i3 ] * 3;
            }
            if ( num == mul5 )
            {
                i5++;
                mul5 = arr[ i5 ] * 5;
            }
        }
        return arr[ n - 1 ];
    }
};
}  // namespace

TEST( UglyNumberII, generic )
{
    {
        Solution sn;
        EXPECT_EQ( 12, sn.nthUglyNumber( 10 ) );
    }
}
