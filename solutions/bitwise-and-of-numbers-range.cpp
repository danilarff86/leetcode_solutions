#include <cmath>
#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    int
    rangeBitwiseAnd( int m, int n )
    {
        auto base = numeric_limits< uint32_t >::max( );
        const auto diff_part = m ^ n;
        int i = 32;
        while ( ( i-- > 0 ) && !( ( 1 << i ) & diff_part ) )
        {
            base >>= 1;
        }
        return n & ~base;
    }
};
}  // namespace

TEST( BitwiseAndOfNumbersRange, generic )
{
    Solution sn;
    EXPECT_EQ( 4, sn.rangeBitwiseAnd( 5, 7 ) );
    EXPECT_EQ( 0, sn.rangeBitwiseAnd( 0, 1 ) );
    EXPECT_EQ( 0, sn.rangeBitwiseAnd( 0, 0 ) );
    EXPECT_EQ( 0, sn.rangeBitwiseAnd( 0, 2147483647 ) );
}
