#pragma once

#include <vector>

namespace binary_tree
{
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode( int x )
        : val( x )
        , left( nullptr )
        , right( nullptr )
    {
    }
};

std::vector< int > bt_to_vec( const TreeNode* node );
TreeNode* bt_from_vec( const std::vector< int >& data );
}  // namespace binary_tree
