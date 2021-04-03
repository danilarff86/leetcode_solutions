#include <queue>
#include "gtest/gtest.h"
#include "linked-list.h"

using namespace std;
using namespace linked_list;

namespace
{
class Solution_heap
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

class Solution
{
public:
    ListNode*
    mergeKLists( vector< ListNode* >& lists )
    {
        if ( lists.empty( ) )
        {
            return nullptr;
        }
        int end = lists.size( ) - 1;
        while ( end > 0 )
        {
            int begin = 0;
            while ( begin < end )
            {
                lists[ begin ] = mergeTwoLists( lists[ begin ], lists[ end ] );
                ++begin;
                --end;
            }
        }
        return lists[ 0 ];
    }

private:
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

TEST( MergeKSortedLinkedLists, generic )
{
    Solution sn;
    {
        vector< ListNode* > lists{list_from_vector( {1, 4, 5} ), list_from_vector( {1, 3, 4} ),
                                  list_from_vector( {2, 6} )};
        EXPECT_EQ( vector< int >( {1, 1, 2, 3, 4, 4, 5, 6} ),
                   list_to_vector( sn.mergeKLists( lists ) ) );
    }
    {
        vector< ListNode* > lists{};
        EXPECT_EQ( vector< int >( ), list_to_vector( sn.mergeKLists( lists ) ) );
    }
}
