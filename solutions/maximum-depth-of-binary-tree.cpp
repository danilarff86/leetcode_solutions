#include "binary-tree.h"
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
        return root == nullptr ? 0
                               : std::max( maxDepth( root->left ), maxDepth( root->right ) ) + 1;
    }
};

}  // namespace

TEST( MaximumDepthOfBinaryTree, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.maxDepth( bt_from_str( "[3, 9, 20, null, null, 15, 7]" ) ) );
}
