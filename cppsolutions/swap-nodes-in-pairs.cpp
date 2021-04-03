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
               list_to_vector( sn.swapPairs( list_from_vector( {1, 2, 3, 4} ) ) ) );
}
