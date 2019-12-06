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
               list_to_vector(
                   sn.addTwoNumbers( list_from_vector( {2} ), list_from_vector( {5, 6, 4} ) ) ) );
    EXPECT_EQ( vector< int >( {8, 1} ), list_to_vector( sn.addTwoNumbers(
                                            list_from_vector( {9} ), list_from_vector( {9} ) ) ) );
    EXPECT_EQ(
        vector< int >( {8, 0, 1} ),
        list_to_vector( sn.addTwoNumbers( list_from_vector( {9} ), list_from_vector( {9, 9} ) ) ) );
    EXPECT_EQ( vector< int >( {7, 0, 8} ),
               list_to_vector( sn.addTwoNumbers( list_from_vector( {2, 4, 3} ),
                                                 list_from_vector( {5, 6, 4} ) ) ) );
    EXPECT_EQ( vector< int >( {0} ), list_to_vector( sn.addTwoNumbers(
                                         list_from_vector( {0} ), list_from_vector( {0} ) ) ) );
    EXPECT_EQ(
        vector< int >( {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} ),
        list_to_vector( sn.addTwoNumbers( list_from_vector( {9} ),
                                          list_from_vector( {1, 9, 9, 9, 9, 9, 9, 9, 9, 9} ) ) ) );
}
