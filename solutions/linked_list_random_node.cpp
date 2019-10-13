#include <cstdlib>

#include "gtest/gtest.h"
#include "linked_list.h"

using namespace std;
using namespace linked_list;

namespace
{
class Solution
{
public:
    Solution( ListNode* head )
        : m_head( head )
        , m_length( 0 )
    {
        while ( head != nullptr )
        {
            ++m_length;
            head = head->next;
        }
    }

    int
    getRandom( )
    {
        int index = rand( ) % m_length;
        auto head = m_head;
        while ( index != 0 )
        {
            head = head->next;
            --index;
        }
        return head->val;
    }

private:
    ListNode* m_head;
    size_t m_length;
};
}  // namespace

TEST( LinkedListRandomNode, generic )
{
    Solution sn( list_from_vector( {1, 2, 3} ) );
    EXPECT_LE( sn.getRandom( ), 3 );
}
