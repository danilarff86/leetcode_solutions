#include "gtest/gtest.h"
#include "linked_list.h"

using namespace std;
using namespace linked_list;

namespace
{
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
               list_to_vector( sn.mergeTwoLists( list_from_vector( {1, 2, 4} ),
                                                 list_from_vector( {1, 3, 4} ) ) ) );
    EXPECT_EQ( vector< int >( ), list_to_vector( sn.mergeTwoLists( list_from_vector( {} ),
                                                                   list_from_vector( {} ) ) ) );
}
