#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution_top_down
{
public:
    TreeNode*
    upsideDownBinaryTree( TreeNode* root )
    {
        auto p = root;
        TreeNode* parent = nullptr;
        TreeNode* parent_right = nullptr;
        while ( p != nullptr )
        {
            // Save next parent
            auto left = p->left;
            // Assign sibling as left
            p->left = parent_right;
            // Save next sibling
            parent_right = p->right;
            // Assign parent as right
            p->right = parent;
            // Next parent and node
            parent = p;
            p = left;
        }
        return parent;
    }
};

class Solution
{
public:
    TreeNode*
    upsideDownBinaryTree( TreeNode* root )
    {
        return dfs_bottom_up( root, nullptr );
    }

private:
    TreeNode*
    dfs_bottom_up( TreeNode* node, TreeNode* parent )
    {
        if ( node == nullptr )
        {
            return parent;
        }
        auto new_root = dfs_bottom_up( node->left, node );
        node->left = ( parent == nullptr ) ? parent : parent->right;
        node->right = parent;
        return new_root;
    }
};
}  // namespace

TEST( BinaryTreeUpsideDown, generic )
{
    Solution sn;
    EXPECT_EQ( "[4, 5, 2, null, null, 3, 1]",
               bt_to_str( sn.upsideDownBinaryTree( bt_from_str( "[1,2,3,4,5]" ) ) ) );
}
