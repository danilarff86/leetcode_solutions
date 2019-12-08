#include "binary-tree.h"
#include "gtest/gtest.h"

TEST( BinaryTree, generic )
{
    {
        auto data = "[5, 1, 4, null, null, 3, 6]";
        EXPECT_EQ( data, binary_tree::bt_to_str( binary_tree::bt_from_str( data ) ) );
    }
}