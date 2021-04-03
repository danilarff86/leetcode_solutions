#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    firstMissingPositive( vector< int >& nums )
    {
        for ( auto& n : nums )
        {
            if ( n <= 0 )
            {
                n = nums.size( ) + 1;
            }
        }

        for ( const auto& n : nums )
        {
            auto pos = abs( n );
            if ( pos <= nums.size( ) && nums[ pos - 1 ] > 0 )
            {
                nums[ pos - 1 ] *= -1;
            }
        }

        int i = 0;
        while ( i < nums.size( ) && nums[ i ] < 0 )
        {
            ++i;
        }
        return i + 1;
    }
};
}  // namespace

TEST( FirstMissingPositive, generic )
{
    Solution sn;
    {
        vector< int > v{1, 2, 0};
        EXPECT_EQ( 3, sn.firstMissingPositive( v ) );
    }
    {
        vector< int > v{3, 4, -1, 1};
        EXPECT_EQ( 2, sn.firstMissingPositive( v ) );
    }
    {
        vector< int > v{7, 8, 9, 11, 12};
        EXPECT_EQ( 1, sn.firstMissingPositive( v ) );
    }
    {
        vector< int > v{1, 2, 3};
        EXPECT_EQ( 4, sn.firstMissingPositive( v ) );
    }
}
