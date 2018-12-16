#include "linked_list.h"

#include <map>

namespace linked_list
{
using namespace std;

ListNodeInfoVec
list_to_vector( const ListNode* node )
{
    vector< int > res;
    while ( node != nullptr )
    {
        res.push_back( node->val );
        node = node->next;
    }
    return res;
}

ListNode*
list_from_vector( const ListNodeInfoVec& data )
{
    ListNode root( 0 );
    ListNode* node = &root;

    for ( auto num : data )
    {
        node->next = new ListNode( num );
        node = node->next;
    }

    return root.next;
}

linked_list::RandomListNodeInfoVec
random_list_to_vector( const RandomListNode* node )
{
    map< const RandomListNode*, int > mapping;
    int i = 0;
    auto p = node;
    while ( p != nullptr )
    {
        mapping[ p ] = i++;
        p = p->next;
    }

    vector< pair< int, int > > res;
    while ( node != nullptr )
    {
        auto index_cit = mapping.find( node->random );
        auto index = index_cit != mapping.end( ) ? index_cit->second : -1;

        res.emplace_back( node->label, index );
        node = node->next;
    }
    return res;
}

RandomListNode*
random_list_from_vector( const RandomListNodeInfoVec& data )
{
    RandomListNode res( 0 );
    RandomListNode* node = &res;

    vector< RandomListNode* > node_ptrs( data.size( ) );
    for ( size_t i = 0; i < data.size( ); ++i )
    {
        node_ptrs[ i ] = new RandomListNode( data[ i ].first );
    }

    for ( size_t i = 0; i < data.size( ); ++i )
    {
        auto random_index = data[ i ].second;
        node_ptrs[ i ]->random = ( random_index >= 0 ) ? node_ptrs[ random_index ] : nullptr;
        node->next = node_ptrs[ i ];
        node = node->next;
    }

    return res.next;
}

}  // namespace linked_list
