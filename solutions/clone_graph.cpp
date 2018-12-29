#include "graph.h"
#include "gtest/gtest.h"

#include <unordered_map>

using namespace std;
using namespace graph;

namespace
{
class Solution
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
