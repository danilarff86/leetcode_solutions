#include <queue>
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
    mergeKLists( const vector< ListNode* >& lists )
    {
        auto comp = []( const ListNode* lhs, const ListNode* rhs ) { return lhs->val > rhs->val; };
        priority_queue< ListNode*, vector< ListNode* >, decltype( comp ) > pq( comp );
        for ( auto list : lists )
        {
            if ( list != nullptr )
            {
                pq.push( list );
            }
        }

        ListNode res( 0 );
        ListNode* res_node = &res;

        while ( !pq.empty( ) )
        {
            auto list = pq.top( );
            pq.pop( );
            res_node->next = list;
            res_node = res_node->next;
            if ( list->next != nullptr )
            {
                pq.push( list->next );
            }
        }

        return res.next;
    }
};
}  // namespace

TEST( MergeKSortedLinkedLists, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {1, 1, 2, 3, 4, 4, 5, 6} ),
               to_vec( sn.mergeKLists( vector< ListNode* >{
                   create_list( {1, 4, 5} ), create_list( {1, 3, 4} ), create_list( {2, 6} )} ) ) );
    EXPECT_EQ( vector< int >( ), to_vec( sn.mergeKLists( vector< ListNode* >{} ) ) );
}
