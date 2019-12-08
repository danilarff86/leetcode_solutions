#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    TreeNode*
    insertIntoBST( TreeNode* root, int val )
    {
        auto node = root;
        while ( node )
        {
            auto& dst = val < node->val ? node->left : node->right;
            if ( dst )
            {
                node = dst;
            }
            else
            {
                dst = new TreeNode( val );
                return root;
            }
        }
        return root;
    }
};

TreeNode*
find_node( TreeNode* node, int val )
{
    if ( !node )
    {
        return nullptr;
    }

    if ( node->val == val )
    {
        return node;
    }

    return val < node->val ? find_node( node->left, val ) : find_node( node->right, val );
}
}  // namespace

TEST( InsertIntoABinarySearchTree, generic )
{
    Solution sn;
    {
        auto bst = bt_from_str( "[4,2,7,1,3]" );
        const auto val = 5;
        auto new_tree = sn.insertIntoBST( bst, val );
        auto node = find_node( new_tree, val );
        ASSERT_TRUE( node && node->val == val );
    }
}
