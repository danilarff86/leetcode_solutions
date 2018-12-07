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
    ListNode* root = nullptr;
    ListNode** list = &root;

    for ( auto num : nums )
    {
        *list = new ListNode( num );
        list = &( ( *list )->next );
    }

    return root;
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
        ListNode* res = nullptr;
        ListNode** res_node = &res;

        while ( l1 != nullptr && l2 != nullptr )
        {
            auto inc_node = l1->val < l2->val ? &l1 : &l2;
            auto tmp_node = *inc_node;
            *inc_node = ( *inc_node )->next;

            *res_node = tmp_node;
            res_node = &( ( *res_node )->next );
        }

        auto final_node = l1 != nullptr ? &l1 : &l2;
        while ( *final_node != nullptr )
        {
            auto tmp_node = *final_node;
            *final_node = ( *final_node )->next;

            *res_node = tmp_node;
            res_node = &( ( *res_node )->next );
        }

        return res;
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
