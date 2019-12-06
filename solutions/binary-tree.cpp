#include "binary-tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <queue>
#include <vector>

namespace binary_tree
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

string
bt_to_str( const TreeNode* root )
{
    if ( root == nullptr )
    {
        return "[]";
    }

    static const auto null_node = "null, ";
    static const auto null_node_len = 6;

    string output = "";
    queue< const TreeNode* > q;
    q.push( root );
    while ( !q.empty( ) )
    {
        auto node = q.front( );
        q.pop( );

        if ( node == nullptr )
        {
            output += null_node;
            continue;
        }

        output += to_string( node->val ) + ", ";
        q.push( node->left );
        q.push( node->right );
    }

    auto compare_with_null = [&](int i) {
        if (i < 0)
        {
            return false;
        }
        int j = 0;
        while (j < null_node_len && output[i++] == null_node[j])
        {
            ++j;
        }
        return j == null_node_len;
    };

    auto output_end = output.length();
    while (compare_with_null(output_end - 6))
    {
        output_end -= 6;
    }

    return "[" + output.substr(0, output_end - 2) + "]";
}

TreeNode*
bt_from_str( const std::string& str )
{
    auto input = get_trim_str( str );
    input = input.substr( 1, input.length( ) - 2 );
    if ( input.empty( ) )
    {
        return nullptr;
    }

    stringstream ss;
    ss.str( input );
    string item;
    char delim = ',';

    if ( !getline( ss, item, delim ) )
    {
        return nullptr;
    }

    TreeNode* root = new TreeNode( std::stoi( item ) );
    queue< TreeNode* > node_queue;
    node_queue.push( root );

    while ( getline( ss, item, delim ) )
    {
        TreeNode* node = node_queue.front( );
        node_queue.pop( );

        item = get_trim_str( item );
        if ( item != "null" )
        {
            node->left = new TreeNode( std::stoi( item ) );
            node_queue.push( node->left );
        }

        if ( !getline( ss, item, delim ) )
        {
            break;
        }
        item = get_trim_str( item );
        if ( item != "null" )
        {
            node->right = new TreeNode( std::stoi( item ) );
            node_queue.push( node->right );
        }
    }

    return root;
}

TEST( BinaryTree, generic )
{
    {
        auto data = "[5, 1, 4, null, null, 3, 6]";
        EXPECT_EQ( data, bt_to_str( bt_from_str( data ) ) );
    }
}

}  // namespace binary_tree
