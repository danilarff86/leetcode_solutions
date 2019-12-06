#include "graph.h"
#include "gtest/gtest.h"

#include <queue>
#include <unordered_map>

using namespace std;
using namespace graph;

namespace
{
class Solution_dfs
{
public:
    UndirectedGraphNode*
    cloneGraph( const UndirectedGraphNode* node )
    {
        if ( node == nullptr )
        {
            return nullptr;
        }
        unordered_map< int, UndirectedGraphNode* > traversed_nodes;
        return dfs( node, traversed_nodes );
    }

private:
    UndirectedGraphNode*
    dfs( const UndirectedGraphNode* node,
         unordered_map< int, UndirectedGraphNode* >& traversed_nodes )
    {
        auto node_it = traversed_nodes.find( node->label );
        if ( node_it != traversed_nodes.end( ) )
        {
            return node_it->second;
        }

        auto new_node = new UndirectedGraphNode( node->label );
        traversed_nodes[ new_node->label ] = new_node;
        for ( const auto neighbor : node->neighbors )
        {
            new_node->neighbors.push_back( dfs( neighbor, traversed_nodes ) );
        }
        return new_node;
    }
};

class Solution
{
public:
    UndirectedGraphNode*
    cloneGraph( const UndirectedGraphNode* root )
    {
        if ( root == nullptr )
        {
            return nullptr;
        }
        unordered_map< int, UndirectedGraphNode* > traversed_nodes;
        auto new_root = traversed_nodes[ root->label ] = new UndirectedGraphNode( root->label );
        queue< const UndirectedGraphNode* > node_queue;
        node_queue.push( root );
        while ( !node_queue.empty( ) )
        {
            auto node = node_queue.front( );
            node_queue.pop( );

            auto cloned_node = traversed_nodes[ node->label ];
            for ( const auto neighbor : node->neighbors )
            {
                auto new_neighbor = traversed_nodes[ neighbor->label ];
                if ( new_neighbor == nullptr )
                {
                    new_neighbor = traversed_nodes[ neighbor->label ]
                        = new UndirectedGraphNode( neighbor->label );
                    node_queue.push( neighbor );
                }
                cloned_node->neighbors.push_back( new_neighbor );
            }
        }
        return new_root;
    }
};
}  // namespace

TEST( CloneGraph, generic )
{
    {
        Solution sn;
        const auto test_data = "{0,1,2#1,2#2,2}";
        EXPECT_EQ( test_data, graph_to_str( sn.cloneGraph( graph_from_str( test_data ) ) ) );
    }
    {
        Solution sn;
        const auto test_data = "{}";
        EXPECT_EQ( test_data, graph_to_str( sn.cloneGraph( graph_from_str( test_data ) ) ) );
    }
}
