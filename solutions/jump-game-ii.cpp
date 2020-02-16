#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    jump( const vector< int >& nums )
    {
        const auto sz = nums.size( );

        int jumps = sz > 1 ? 1 : 0;

        auto step_limit = nums[ 0 ];
        auto all_step_limit = step_limit;

        for ( size_t i = 0; i < sz - 1; i++ )
        {
            if ( i + nums[ i ] > step_limit )
            {
                step_limit = i + nums[ i ];
            }
            if ( i == all_step_limit )
            {
                ++jumps;
                all_step_limit = step_limit;
            }
        }

        return jumps;
    }
};
}  // namespace

TEST( JumpGameII, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.jump( {2, 3, 1, 1, 4} ) );
}
