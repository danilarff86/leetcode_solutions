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
        while ( i < j && nums[ i ] > nums[ j ] )
        {
            const int m = ( i + j ) / 2;
            if ( nums[ m ] > nums[ j ] )
            {
                i = m + 1;
            }
            else
            {
                j = m;
            }
        }
        return nums[ i ];
    }
};
}  // namespace

TEST( FindMinimumInRotatedSortedArray, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.findMin( {3, 4, 5, 1, 2} ) );
    EXPECT_EQ( 0, sn.findMin( {4, 5, 6, 7, 0, 1, 2} ) );
}
