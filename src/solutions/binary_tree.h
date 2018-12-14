#pragma once

#include <string>

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

std::string bt_to_str(const TreeNode* root);
TreeNode* bt_from_str(const std::string & str);
}  // namespace binary_tree
