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
    maxDepth( const TreeNode* root )
    {
        return max_depth( root, 0 );
    }

private:
    int
    max_depth( const TreeNode* node, int level )
    {
        return node != nullptr ? std::max( max_depth( node->left, level + 1 ),
                                           max_depth( node->right, level + 1 ) )
                               : level;
    }
};

}  // namespace

TEST( MaximumDepthOfBinaryTree, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.maxDepth( bt_from_vec( {3, 9, 20, -1, -1, 15, 7} ) ) );
}
