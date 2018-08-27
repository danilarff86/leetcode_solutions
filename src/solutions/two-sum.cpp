#include "gtest/gtest.h"
#include <vector>
#include <unordered_map>

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    twoSum( vector< int >& nums, int target )
    {
        unordered_map< int, int > num2index;
        for ( int i = 0; i < int( nums.size( ) ); ++i )
        {
            auto const val = nums[ i ];
            auto const diff_val = target - val;

            auto it = num2index.find( diff_val );
            if ( it != num2index.end( ) )
            {
                return {it->second, i};
            }

            num2index[ nums[ i ] ] = i;
        }

        return {};
    }
};
}  // namespace

TEST( TwoSum, generic )
{
    vector< int > nums = {2, 7, 11, 15};
    Solution sn;
    const vector< int > expected = {0, 1};

    EXPECT_EQ( expected, sn.twoSum( nums, 9 ) );
}