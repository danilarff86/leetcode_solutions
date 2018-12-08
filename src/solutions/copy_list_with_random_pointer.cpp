#include "gtest/gtest.h"
#include "linked_list.h"

#include <unordered_map>

using namespace std;
using namespace linked_list;

namespace
{
class Solution_hash
{
public:
    RandomListNode*
    copyRandomList( RandomListNode* head )
    {
        unordered_map< RandomListNode*, RandomListNode* > mapping;
        RandomListNode res( 0 );
        auto res_node = &res;
        auto head_node = head;
        while ( head_node != nullptr )
        {
            res_node->next = new RandomListNode( head_node->label );
            mapping[ head_node ] = res_node->next;
            head_node = head_node->next;
            res_node = res_node->next;
        }

        res_node = &res;
        head_node = head;
        while ( head_node != nullptr )
        {
            res_node->next->random = mapping[ head_node->random ];
            head_node = head_node->next;
            res_node = res_node->next;
        }

        return res.next;
    }
};

class Solution
{
public:
    RandomListNode*
    copyRandomList( RandomListNode* head )
    {
        auto head_node = head;
        while ( head_node != nullptr )
        {
            auto new_node = new RandomListNode( head_node->label );
            new_node->next = head_node->next;
            head_node->next = new_node;
            head_node = head_node->next->next;
        }

        head_node = head;
        while ( head_node != nullptr )
        {
            if ( head_node->random != nullptr )
            {
                head_node->next->random = head_node->random->next;
            }
            head_node = head_node->next->next;
        }

        RandomListNode res( 0 );
        auto res_node = &res;
        head_node = head;
        while ( head_node != nullptr )
        {
            res_node->next = head_node->next;
            head_node->next = head_node->next->next;
            head_node = head_node->next;
            res_node = res_node->next;
        }

        return res.next;
    }
};
}  // namespace

TEST( CopyListWithRandomPointer, generic )
{
    Solution sn;
    {
        RandomListNodeInfoVec v{{1, -1}, {2, 0}};
        EXPECT_EQ( v, random_list_to_vector( sn.copyRandomList( random_list_from_vector( v ) ) ) );
    }
}
