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
        return array_to_tree( nums, 0, nums.size( ) - 1 );
    }

private:
    TreeNode*
    array_to_tree( vector< int >& nums, int start, int end )
    {
        if ( start > end )
        {
            return nullptr;
        }
        const auto middle = ( end + start ) / 2;
        auto node = new TreeNode( nums[ middle ] );
        node->left = array_to_tree( nums, start, middle - 1 );
        node->right = array_to_tree( nums, middle + 1, end );
        return node;
    }
};
}  // namespace

TEST( ConvertSortedArrayToBalancedBinarySearchTree, generic )
{
    Solution sn;
    EXPECT_EQ( "[0, -10, 5, null, -3, null, 9]",
               bt_to_str( sn.sortedArrayToBST( vector< int >{-10, -3, 0, 5, 9} ) ) );
}
