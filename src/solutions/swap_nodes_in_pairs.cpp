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
    swapPairs( ListNode* head )
    {
        ListNode root( 0 );
        ListNode* node = &root;
        node->next = head;

        while ( node->next != nullptr && node->next->next != nullptr )
        {
            auto temp = node->next;
            node->next = node->next->next;
            temp->next = node->next->next;
            node->next->next = temp;
            node = temp;
        }

        return root.next;
    }
};
}  // namespace

TEST( SwapNodesInPairs, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {2, 1, 4, 3} ),
               to_vec( sn.swapPairs( create_list( {1, 2, 3, 4} ) ) ) );
}
