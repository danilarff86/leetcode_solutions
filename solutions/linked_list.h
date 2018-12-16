#pragma once

#include <utility>
#include <vector>

namespace linked_list
{
struct ListNode
{
    int val;
    ListNode* next;
    ListNode( int x )
        : val( x )
        , next( nullptr )
    {
    }
};

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode( int x )
        : label( x )
        , next( nullptr )
        , random( nullptr )
    {
    }
};

using ListNodeInfoVec = std::vector< int >;
using RandomListNodeInfo = std::pair< int, int >;
using RandomListNodeInfoVec = std::vector< RandomListNodeInfo >;

ListNodeInfoVec list_to_vector( const ListNode* node );
ListNode* list_from_vector( const ListNodeInfoVec& data );
RandomListNodeInfoVec random_list_to_vector( const RandomListNode* node );
RandomListNode* random_list_from_vector( const RandomListNodeInfoVec& data );
}  // namespace linked_list
