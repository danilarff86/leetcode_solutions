#include <queue>
#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    bool
    isCousins( TreeNode* root, int x, int y )
    {
        struct Entry
        {
            TreeNode* node;
            TreeNode* parent;
            int level;
        };

        queue< Entry > q;
        q.push( Entry{root, nullptr, 0} );

        Entry x_node_entry{};
        Entry y_node_entry{};

        while ( !q.empty( ) )
        {
            auto entry = q.front( );
            q.pop( );

            if ( entry.node != nullptr )
            {
                if ( entry.node->val == x )
                {
                    x_node_entry = entry;
                }
                else if ( entry.node->val == y )
                {
                    y_node_entry = entry;
                }
                else
                {
                    q.push( Entry{entry.node->left, entry.node, entry.level + 1} );
                    q.push( Entry{entry.node->right, entry.node, entry.level + 1} );
                }
            }
        }

        return x_node_entry.node != nullptr && y_node_entry.node != nullptr
               && x_node_entry.level == y_node_entry.level
               && x_node_entry.parent != y_node_entry.parent;
    }
};
}  // namespace

TEST( CousinsInBinaryTree, generic )
{
    Solution sn;
    EXPECT_FALSE( sn.isCousins( bt_from_str( "[1,2,3,4]" ), 4, 3 ) );
    EXPECT_TRUE( sn.isCousins( bt_from_str( "[1,2,3,null,4,null,5]" ), 5, 4 ) );
    EXPECT_FALSE( sn.isCousins( bt_from_str( "[1,2,3,null,4]" ), 2, 3 ) );
}
