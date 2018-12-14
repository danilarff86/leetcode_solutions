#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <queue>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution_depth_first_traversal
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

class Solution
{
public:
    int
    minDepth( const TreeNode* root )
    {
        if ( root == nullptr )
        {
            return 0;
        }
        int depth = 1;
        auto* right_most = root;
        queue< const TreeNode* > q;
        q.push( root );
        while ( !q.empty( ) )
        {
            auto node = q.front( );
            q.pop( );
            if ( node->right == nullptr && node->left == nullptr )
            {
                break;
            }
            if ( node->left != nullptr )
            {
                q.push( node->left );
            }
            if ( node->right != nullptr )
            {
                q.push( node->right );
            }
            if ( node == right_most )
            {
                ++depth;
                right_most = ( node->right != nullptr ) ? node->right : node->left;
            }
        }
        return depth;
    }
};

}  // namespace

TEST( MinimumDepthOfBinaryTree, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.minDepth( bt_from_str( "[3, 9, 20, null, null, 15, 7]" ) ) );
    EXPECT_EQ( 2, sn.minDepth( bt_from_str( "[1, 2]" ) ) );
}
