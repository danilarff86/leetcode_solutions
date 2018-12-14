#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    TreeNode*
    sortedArrayToBST( vector< int >& nums )
    {
        TreeNode* root = nullptr;
        if ( !nums.empty( ) )
        {
            root = new TreeNode( 0 );
            array_to_tree( root, nums.begin( ), nums.end( ) );
        }
        return root;
    }

private:
    void
    array_to_tree( TreeNode* node,
                   vector< int >::const_iterator start,
                   vector< int >::const_iterator end )
    {
        const auto lenght = distance( start, end );
        const auto half_lenght = lenght / 2u;
        node->val = *( start + half_lenght );
        if ( half_lenght > 0 )
        {
            node->left = new TreeNode( 0 );
            array_to_tree( node->left, start, start + half_lenght );
        }
        if ( ( half_lenght + 1 ) < lenght )
        {
            node->right = new TreeNode( 0 );
            array_to_tree( node->right, start + half_lenght + 1, end );
        }
    }
};
}  // namespace

TEST( ConvertSortedArrayToBalancedBinarySearchTree, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {0, -3, 9, -10, -1, 5} ),
               bt_to_vec( sn.sortedArrayToBST( vector< int >{-10, -3, 0, 5, 9} ) ) );
}
