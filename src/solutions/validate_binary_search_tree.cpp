#include "binary_tree.h"
#include "gtest/gtest.h"

#include <limits>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    bool
    isValidBST( TreeNode* root )
    {
        return is_valid_subtree( root, nullptr, nullptr );
    }

private:
    bool
    is_valid_subtree( TreeNode* node, TreeNode* left_node, TreeNode* right_node )
    {
        if ( node != nullptr )
        {
            const auto node_valid = ( left_node == nullptr || node->val > left_node->val )
                                    && ( right_node == nullptr || node->val < right_node->val );
            return node_valid && is_valid_subtree( node->left, left_node, node )
                   && is_valid_subtree( node->right, node, right_node );
        }

        return true;
    }
};
}  // namespace

TEST( ValidateBinarySearchTree, generic )
{
    Solution sn;
    EXPECT_FALSE( sn.isValidBST( bt_from_vec( {5, 1, 4, -1, -1, 3, 6} ) ) );
    EXPECT_TRUE( sn.isValidBST( bt_from_vec( {2, 1, 3} ) ) );
    EXPECT_FALSE( sn.isValidBST( bt_from_vec( {int( -2147483648 ), int( -2147483648 )} ) ) );
}