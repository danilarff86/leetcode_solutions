#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    int
    rangeSumBST( TreeNode* root, int L, int R )
    {
        res = 0;
        recursive( root, L, R );
        return res;
    }

private:
    void
    recursive( TreeNode* node, int L, int R )
    {
        if ( node != nullptr )
        {
            if ( node->val >= L && node->val <= R )
            {
                res += node->val;
            }
            if ( node->val > L )
            {
                recursive( node->left, L, R );
            }
            if ( node->val < R )
            {
                recursive( node->right, L, R );
            }
        }
    }
    int res;
};
}  // namespace

TEST( RangeSumOfBST, generic )
{
    Solution sn;
    EXPECT_EQ( 32, sn.rangeSumBST( bt_from_str( "[10,5,15,3,7,null,18]" ), 7, 15 ) );
    EXPECT_EQ( 23, sn.rangeSumBST( bt_from_str( "[10,5,15,3,7,13,18,1,null,6]" ), 6, 10 ) );
}
