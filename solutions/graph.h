#pragma once

#include <string>
#include <vector>

namespace graph
{
struct UndirectedGraphNode
{
    int label;
    std::vector< UndirectedGraphNode* > neighbors;
    UndirectedGraphNode( int x )
        : label( x ){};
};

UndirectedGraphNode* graph_from_str( const std::string& str );
std::string graph_to_str( const UndirectedGraphNode* node );
}  // namespace graph
