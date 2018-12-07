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
    mergeTwoLists( ListNode* l1, ListNode* l2 )
    {
        ListNode res( 0 );
        ListNode* res_node = &res;

        while ( l1 != nullptr && l2 != nullptr )
        {
            if ( l1->val < l2->val )
            {
                res_node->next = l1;
                l1 = l1->next;
            }
            else
            {
                res_node->next = l2;
                l2 = l2->next;
            }
            res_node = res_node->next;
        }

        if ( l1 != nullptr )
        {
            res_node->next = l1;
        }
        else
        {
            res_node->next = l2;
        }

        return res.next;
    }
};
}  // namespace

TEST( MergeTwoSortedLists, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {1, 1, 2, 3, 4, 4} ),
               to_vec( sn.mergeTwoLists( create_list( {1, 2, 4} ), create_list( {1, 3, 4} ) ) ) );
    EXPECT_EQ( vector< int >( ),
               to_vec( sn.mergeTwoLists( create_list( {} ), create_list( {} ) ) ) );
}
