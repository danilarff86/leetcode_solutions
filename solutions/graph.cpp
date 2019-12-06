#include "graph.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace graph
{
using namespace std;

string
get_trim_str( const string& str )
{
    auto res = str;
    res.erase( res.begin( ),
               find_if( res.begin( ), res.end( ), []( int ch ) { return !isspace( ch ); } ) );
    res.erase(
        find_if( res.rbegin( ), res.rend( ), []( int ch ) { return !isspace( ch ); } ).base( ),
        res.end( ) );
    return res;
}

UndirectedGraphNode*
process_node( const string& str, unordered_map< int, UndirectedGraphNode* >& all_nodes )
{
    stringstream ss;
    ss.str( str );
    string item;
    const char delim = ',';

    if ( !getline( ss, item, delim ) )
    {
        return nullptr;
    }

    auto num = stoi( item );
    auto node = all_nodes[ num ];
    if ( node == nullptr )
    {
        node = all_nodes[ num ] = new UndirectedGraphNode( num );
    }

    while ( getline( ss, item, delim ) )
    {
        num = stoi( item );
        auto neighbor = all_nodes[ num ];
        if ( neighbor == nullptr )
        {
            neighbor = all_nodes[ num ] = new UndirectedGraphNode( num );
        }
        node->neighbors.push_back( neighbor );
    }

    return node;
}

UndirectedGraphNode*
graph_from_str( const string& str )
{
    auto input = get_trim_str( str );
    input = input.substr( 1, input.length( ) - 2 );
    if ( input.empty( ) )
    {
        return nullptr;
    }

    stringstream ss;
    ss.str( input );
    string node_item;
    const char node_delim = '#';

    unordered_map< int, UndirectedGraphNode* > all_nodes;

    if ( !getline( ss, node_item, node_delim ) )
    {
        return nullptr;
    }

    auto root = process_node( node_item, all_nodes );
    while ( getline( ss, node_item, node_delim ) )
    {
        process_node( node_item, all_nodes );
    }

    return root;
}

string
graph_to_str( const UndirectedGraphNode* root )
{
    if ( root == nullptr )
    {
        return "{}";
    }

    unordered_set< const UndirectedGraphNode* > processed_nodes;

    string output = "";
    queue< const UndirectedGraphNode* > q;
    q.push( root );
    while ( !q.empty( ) )
    {
        auto node = q.front( );
        q.pop( );

        if ( processed_nodes.find( node ) != processed_nodes.end( ) )
        {
            continue;
        }

        processed_nodes.insert( node );

        output += "#" + to_string( node->label );
        for ( const auto neighbor : node->neighbors )
        {
            q.push( neighbor );
            output += "," + to_string( neighbor->label );
        }
    }

    return "{" + output.substr( 1 ) + "}";
}

TEST( Graph, generic )
{
    {
        auto data = "{0,1,2#1,2#2,2}";
        EXPECT_EQ( data, graph_to_str( graph_from_str( data ) ) );
    }
    {
        auto data = "{}";
        EXPECT_EQ( data, graph_to_str( graph_from_str( data ) ) );
    }
}

}  // namespace graph
