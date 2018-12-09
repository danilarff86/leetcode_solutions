#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    int
    minDepth( TreeNode* root )
    {
        if ( root == nullptr )
        {
            return 0;
        }
        if ( root->left == nullptr )
        {
            return minDepth( root->right ) + 1;
        }
        if ( root->right == nullptr )
        {
            return minDepth( root->left ) + 1;
        }
        return std::min( minDepth( root->left ), minDepth( root->right ) ) + 1;
    }
};

}  // namespace

TEST( MinimumDepthOfBinaryTree, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.minDepth( bt_from_vec( {3, 9, 20, -1, -1, 15, 7} ) ) );
    EXPECT_EQ( 2, sn.minDepth( bt_from_vec( {1, 2} ) ) );
}
