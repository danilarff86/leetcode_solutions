#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    searchInsert( const vector< int >& nums, int target )
    {
        int i = 0;
        int j = nums.size( ) - 1;
        while ( i < j )
        {
            const int m = ( i + j ) / 2;
            if ( target > nums[ m ] )
            {
                i = m + 1;
            }
            else
            {
                j = m;
            }
        }
        return target > nums[ i ] ? i + 1 : i;
    }
};
}  // namespace

TEST( SearchInsertPosition, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.searchInsert( {1, 3, 5, 6}, 5 ) );
    EXPECT_EQ( 1, sn.searchInsert( {1, 3, 5, 6}, 2 ) );
    EXPECT_EQ( 4, sn.searchInsert( {1, 3, 5, 6}, 7 ) );
    EXPECT_EQ( 0, sn.searchInsert( {1, 3, 5, 6}, 0 ) );
}
