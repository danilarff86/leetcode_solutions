#include "gtest/gtest.h"

#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    singleNumber( const vector< int >& nums )
    {
        int res = 0;
        for ( const auto n : nums )
        {
            res ^= n;
        }
        return res;
    }
};
}  // namespace

TEST( SingleNumber, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.singleNumber( {2, 2, 1} ) );
    EXPECT_EQ( 4, sn.singleNumber( {4, 1, 2, 1, 2} ) );
}
