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
    partition( ListNode* head, int x )
    {
        ListNode left( 0 );
        ListNode right( 0 );
        auto p_left = &left;
        auto p_right = &right;
        while ( head )
        {
            if ( head->val < x )
            {
                p_left->next = head;
                p_left = p_left->next;
            }
            else
            {
                p_right->next = head;
                p_right = p_right->next;
            }
            head = head->next;
        }
        p_right->next = nullptr;
        p_left->next = right.next;
        return left.next;
    }
};
}  // namespace

TEST( PartitionList, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {1, 2, 2, 4, 3, 5} ),
               list_to_vector( sn.partition( list_from_vector( {1, 4, 3, 2, 5, 2} ), 3 ) ) );
}
