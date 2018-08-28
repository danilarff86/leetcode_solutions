#include <unordered_map>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    twoSum( vector< int >& numbers, int target )
    {
        int i = 0;
        int j = numbers.size( ) - 1;
        while ( i < j )
        {
            auto sum = numbers[ i ] + numbers[ j ];
            if ( sum < target )
            {
                ++i;
            }
            else if ( sum > target )
            {
                --j;
            }
            else
            {
                return {i + 1, j + 1};
            }
        }
        return {};
    }
};
}  // namespace

TEST( TwoSum_II, generic )
{
    vector< int > nums = {2, 7, 11, 15};
    Solution sn;
    const vector< int > expected = {1, 2};

    EXPECT_EQ( expected, sn.twoSum( nums, 9 ) );
}