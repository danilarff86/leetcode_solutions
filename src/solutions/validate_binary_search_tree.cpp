#include "binary_tree.h"
#include "gtest/gtest.h"

#include <cstdint>
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
        return is_valid_subtree( root, numeric_limits< int64_t >::min( ),
                                 numeric_limits< int64_t >::max( ) );
    }

private:
    bool
    is_valid_subtree( TreeNode* node, int64_t min_val, int64_t max_val )
    {
        if ( node != nullptr )
        {
            const auto node_val = int64_t( node->val );
            auto const node_valid = node_val >= min_val && node_val <= max_val;
            return node_valid && is_valid_subtree( node->left, min_val, node_val - 1 )
                   && is_valid_subtree( node->right, node_val + 1, max_val );
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
