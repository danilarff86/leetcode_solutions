#include "gtest/gtest.h"
#include "linked-list.h"

using namespace std;
using namespace linked_list;

namespace
{
class Solution
{
public:
    ListNode*
    reverseKGroup( ListNode* head, int k )
    {
        ListNode dummy( 0 );
        dummy.next = head;
        ListNode* group_end = &dummy;
        for ( ;; )
        {
            auto group_parent = group_end;
            int group_cnt = k;

            while ( group_end != nullptr && group_cnt-- > 0 )
            {
                group_end = group_end->next;
            }

            if ( group_end == nullptr )
            {
                break;
            }

            auto next_group = group_end->next;

            auto node = group_parent->next;
            auto node_parent = node->next;

            while ( node_parent != next_group )
            {

                auto next = node_parent->next;
                node_parent->next = node;
                node = node_parent;
                node_parent = next;
            }

            group_end = group_parent->next;
            group_parent->next->next = next_group;
            group_parent->next = node;
        }

        return dummy.next;
    }
};
}  // namespace

TEST( ReverseNodesInKGroup, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< int >{2, 1, 4, 3, 5} ),
               list_to_vector( sn.reverseKGroup( list_from_vector( {1, 2, 3, 4, 5} ), 2 ) ) );
    EXPECT_EQ( ( vector< int >{3, 2, 1, 4, 5} ),
               list_to_vector( sn.reverseKGroup( list_from_vector( {1, 2, 3, 4, 5} ), 3 ) ) );
}
