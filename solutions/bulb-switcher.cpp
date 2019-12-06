#include "gtest/gtest.h"

#include <cmath>

using namespace std;

namespace
{
/* Each element is switched NUM DIVIDERS times. In case when NUM_DIVIDERS is odd element is toggled,
 * otherwise - not. The number of dividers for number which has no integral sqare is always even. If
 * N / D1 = D2, then N / D2 = D1. If it has square root we have additional divider N / D = D, and
 * whole number of dividers is odd. So only elements which square roots are toggled. So the next
 * elements are toggled: 1^2, 2^2, 3^2, 4^2, K^2. So, we have K elements which are would be toggled.
 * K^2 <= N, so that K <= SQRT(N). Solution is floor(sqrt(N)).
 */

class Solution
{
public:
    int
    bulbSwitch( int n )
    {
        return sqrt( n );
    }
};
}  // namespace

TEST( BulbSwitcher, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.bulbSwitch( 3 ) );
}
