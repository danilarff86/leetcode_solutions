#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <climits>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    int
    maxPathSum( const TreeNode* root )
    {
        max_path_sum = numeric_limits< int >::min( );
        calc_max_path_sum( root );
        return max_path_sum;
    }
    int
    calc_max_path_sum( const TreeNode* node )
    {
        if ( node == nullptr )
        {
            return 0;
        }

        const auto val = node->val;
        const auto left_sum = calc_max_path_sum( node->left );
        const auto right_sum = calc_max_path_sum( node->right );
        max_path_sum = max( max_path_sum, val + left_sum + right_sum );

        const auto ret = val + max( left_sum, right_sum );
        return ret > 0 ? ret : 0;
    }

private:
    int max_path_sum;
};
}  // namespace

TEST( BinaryTreeMaximumPathSum, generic )
{
    Solution sn;
    EXPECT_EQ( 6, sn.maxPathSum( bt_from_str( "[1,2,3]" ) ) );
    EXPECT_EQ( 42, sn.maxPathSum( bt_from_str( "[-10,9,20,null,null,15,7]" ) ) );
}
