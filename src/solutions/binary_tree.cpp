#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <queue>

namespace binary_tree
{
using namespace std;

vector< int >
bt_to_vec( const TreeNode* node )
{
    if ( node == nullptr )
    {
        return {};
    }

    queue< const TreeNode* > node_queue;
    node_queue.push( node );
    vector< int > res;
    res.push_back( node->val );

    while ( !node_queue.empty( ) )
    {
        auto node = node_queue.front( );
        node_queue.pop( );

        if ( node->left != nullptr )
        {
            res.push_back( node->left->val );
            node_queue.push( node->left );
        }
        else
        {
            res.push_back( -1 );
        }

        if ( node->right != nullptr )
        {
            res.push_back( node->right->val );
            node_queue.push( node->right );
        }
        else
        {
            res.push_back( -1 );
        }
    }

    res.erase( find_if( res.rbegin( ), res.rend( ), []( int v ) { return v >= 0; } ).base( ),
               res.end( ) );

    return res;
}

TreeNode*
bt_from_vec( const vector< int >& data )
{
    if ( data.empty( ) )
    {
        return nullptr;
    }

    auto data_it = data.begin( );

    TreeNode* root = new TreeNode( *data_it++ );
    queue< TreeNode* > node_queue;
    node_queue.push( root );

    while ( data_it != data.end( ) )
    {
        TreeNode* node = node_queue.front( );
        node_queue.pop( );

        auto item = *data_it++;

        if ( item != -1 )
        {
            node->left = new TreeNode( item );
            node_queue.push( node->left );
        }

        if ( data_it == data.end( ) )
        {
            break;
        }

        item = *data_it++;

        if ( item != -1 )
        {
            node->right = new TreeNode( item );
            node_queue.push( node->right );
        }
    }

    return root;
}

TEST( BinaryTree, generic )
{
    {
        vector< int > v{5, 1, 4, -1, -1, 3, 6};
        EXPECT_EQ( v, bt_to_vec( bt_from_vec( v ) ) );
    }
}

}  // namespace binary_tree
