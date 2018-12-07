#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
struct ListNode
{
    int val;
    ListNode* next;
    ListNode( int x )
        : val( x )
        , next( NULL )
    {
    }
};

ListNode*
create_list( const vector< int >& nums )
{
    ListNode root( 0 );
    ListNode* node = &root;

    for ( auto num : nums )
    {
        node->next = new ListNode( num );
        node = node->next;
    }

    return root.next;
}

vector< int >
to_vec( const ListNode* node )
{
    vector< int > res;
    while ( node != nullptr )
    {
        res.push_back( node->val );
        node = node->next;
    }
    return res;
}

class Solution
{
public:
    ListNode*
    addTwoNumbers( ListNode* l1, ListNode* l2 )
    {
        ListNode res( 0 );
        ListNode* res_node = &res;

        int carried = 0;
        while ( l1 != nullptr || l2 != nullptr )
        {
            if ( l1 != nullptr )
            {
                carried += l1->val;
                res_node->next = l1;
                l1 = l1->next;
            }
            if ( l2 != nullptr )
            {
                carried += l2->val;
                res_node->next = l2;
                l2 = l2->next;
            }

            res_node = res_node->next;
            if ( carried >= 10 )
            {
                res_node->val = carried - 10;
                carried = 1;
            }
            else
            {
                res_node->val = carried;
                carried = 0;
            }
        }

        if ( carried )
        {
            res_node->next = new ListNode( 1 );
        }

        return res.next;
    }
};
}  // namespace

TEST( AddTwoNumbers, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {7, 6, 4} ),
               to_vec( sn.addTwoNumbers( create_list( {2} ), create_list( {5, 6, 4} ) ) ) );
    EXPECT_EQ( vector< int >( {8, 1} ),
               to_vec( sn.addTwoNumbers( create_list( {9} ), create_list( {9} ) ) ) );
    EXPECT_EQ( vector< int >( {8, 0, 1} ),
               to_vec( sn.addTwoNumbers( create_list( {9} ), create_list( {9, 9} ) ) ) );
    EXPECT_EQ( vector< int >( {7, 0, 8} ),
               to_vec( sn.addTwoNumbers( create_list( {2, 4, 3} ), create_list( {5, 6, 4} ) ) ) );
    EXPECT_EQ( vector< int >( {0} ),
               to_vec( sn.addTwoNumbers( create_list( {0} ), create_list( {0} ) ) ) );
    EXPECT_EQ( vector< int >( {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} ),
               to_vec( sn.addTwoNumbers( create_list( {9} ),
                                         create_list( {1, 9, 9, 9, 9, 9, 9, 9, 9, 9} ) ) ) );
}
