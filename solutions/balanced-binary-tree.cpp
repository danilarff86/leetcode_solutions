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
    bool
    isBalanced( const TreeNode* root )
    {
        return max_depth( root ) != -1;
    }

private:
    int
    max_depth( const TreeNode* node )
    {
        if ( node == nullptr )
        {
            return 0;
        }

        const int L = max_depth( node->left );
        if ( L == -1 )
        {
            return -1;
        }

        const int R = max_depth( node->right );
        if ( R == -1 )
        {
            return -1;
        }

        return ( std::abs( L - R ) <= 1 ) ? ( std::max( L, R ) + 1 ) : -1;
    }
};

}  // namespace

TEST( BalancedBinaryTree, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isBalanced( bt_from_str( "[3, 9, 20, null, null, 15, 7]" ) ) );
    EXPECT_FALSE( sn.isBalanced( bt_from_str( "[1, 2, 2, 3, 3, null, null, 4, 4]" ) ) );
}
