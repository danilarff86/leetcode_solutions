#include "gtest/gtest.h"
#include "linked-list.h"

using namespace std;
using namespace linked_list;

namespace merge_lists
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
}  // namespace merge_lists

namespace merge_arrays
{
class Solution
{
public:
    vector< int >
    mergeArrays( const vector< int >& v1, const vector< int >& v2 )
    {
        vector< int > res( v1.size( ) + v2.size( ) );
        auto it1 = v1.begin( );
        auto it2 = v2.begin( );
        auto itRes = res.begin( );

        while ( it1 != v1.end( ) && it2 != v2.end( ) )
        {
            if ( *it1 < *it2 )
            {
                *itRes++ = *it1++;
            }
            else
            {
                *itRes++ = *it2++;
            }
        }

        auto itBegin = it1 != v1.end( ) ? it1 : it2;
        auto itEnd = it1 != v1.end( ) ? v1.end( ) : v2.end( );

        std::copy( itBegin, itEnd, itRes );

        return res;
    }
};
}  // namespace merge_arrays

TEST( MergeTwoSortedLists, generic )
{
    {
        merge_lists::Solution sn;
        EXPECT_EQ( vector< int >( {1, 1, 2, 3, 4, 4} ),
                   list_to_vector( sn.mergeTwoLists( list_from_vector( {1, 2, 4} ),
                                                     list_from_vector( {1, 3, 4} ) ) ) );
        EXPECT_EQ( vector< int >( ), list_to_vector( sn.mergeTwoLists( list_from_vector( {} ),
                                                                       list_from_vector( {} ) ) ) );
    }
    {
        merge_arrays::Solution sn;
        EXPECT_EQ( vector< int >( {1, 1, 2, 3, 4, 4} ), sn.mergeArrays( {1, 2, 4}, {1, 3, 4} ) );
        EXPECT_EQ( vector< int >( ), sn.mergeArrays( {}, {} ) );
    }
}
