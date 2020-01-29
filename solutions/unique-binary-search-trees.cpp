#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    numTrees( int n )
    {
        vector< int > dp( n + 1 );
        dp[ 0 ] = 1;
        dp[ 1 ] = 1;

        // We can use the fact that if 'i' is the root, then i-1 numbers will be in left subtree and
        // n-(i+1) in right subtree.
        for ( int i = 2; i <= n; ++i )
        {
            for ( int j = 0; j < i; ++j )
            {
                dp[ i ] += dp[ j ] * dp[ i - 1 - j ];
            }
        }

        return dp[ n ];
    }
};
}  // namespace

TEST( UniqueBinarySearchTrees, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.numTrees( 2 ) );
    EXPECT_EQ( 5, sn.numTrees( 3 ) );
    EXPECT_EQ( 14, sn.numTrees( 4 ) );
}
