#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    findMin( const vector< int >& nums )
    {
        int i = 0;
        int j = nums.size( ) - 1;
        while ( i < j && nums[ i ] >= nums[ j ] )
        {
            const int m = ( i + j ) / 2;
            if ( nums[ m ] > nums[ j ] )
            {
                i = m + 1;
            }
            else if ( nums[ m ] < nums[ i ] )
            {
                j = m;
            }
            else
            {
                ++i;
            }
        }
        return nums[ i ];
    }
};
}  // namespace

TEST( FindMinimumInRotatedSortedArrayII, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.findMin( {1, 3, 5} ) );
    EXPECT_EQ( 0, sn.findMin( {2, 2, 2, 0, 1} ) );
    EXPECT_EQ( 1, sn.findMin( {3, 1, 3} ) );
}
