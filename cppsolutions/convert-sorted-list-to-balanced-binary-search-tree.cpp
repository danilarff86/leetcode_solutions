#include "binary-tree.h"
#include "gtest/gtest.h"
#include "linked-list.h"

using namespace std;
using namespace binary_tree;
using namespace linked_list;

namespace
{
class Solution
{
public:
    TreeNode*
    sortedListToBST( const ListNode* head )
    {
        node = head;
        int n = 0;
        while ( head != nullptr )
        {
            head = head->next;
            ++n;
        }
        const auto res = sorted_list_to_bst( 0, n - 1 );
        return res;
    }

private:
    TreeNode*
    sorted_list_to_bst( int begin, int end )
    {
        if ( begin > end )
        {
            return nullptr;
        }
        const auto middle = ( begin + end ) / 2;
        const auto left_node = sorted_list_to_bst( begin, middle - 1 );
        auto res = new TreeNode( node->val );
        res->left = left_node;
        node = node->next;
        res->right = sorted_list_to_bst( middle + 1, end );
        return res;
    }

private:
    const ListNode* node;
};
}  // namespace

TEST( ConvertSortedListToBalancedBinarySearchTree, generic )
{
    Solution sn;
    EXPECT_EQ(
        "[0, -10, 5, null, -3, null, 9]",
        bt_to_str( sn.sortedListToBST( list_from_vector( vector< int >{-10, -3, 0, 5, 9} ) ) ) );
}
