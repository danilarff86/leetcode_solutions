#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace
{
class Solution
{
public:
    void
    recoverTree( TreeNode* root )
    {
        prev = NULL;
        while ( !in_order( root ) )
        {
            prev = NULL;
        }
    }

private:
    TreeNode* prev;

    bool
    in_order( TreeNode* p )
    {
        if ( p == NULL )
        {
            return true;
        }

        if ( in_order( p->left ) )
        {
            if ( prev != NULL && prev->val > p->val )
            {
                std::swap( prev->val, p->val );
                return false;
            }
            prev = p;
            return in_order( p->right );
        }

        return false;
    }
};
}  // namespace

TEST( RecoverBinarySearchTree, generic )
{
    Solution sn;
    {
        auto tree = bt_from_str( "[1,3,null,null,2]" );
        sn.recoverTree( tree );
        EXPECT_EQ( "[3, 1, null, null, 2]", bt_to_str( tree ) );
    }
    {
        auto tree = bt_from_str( "[3,1,4,null,null,2]" );
        sn.recoverTree( tree );
        EXPECT_EQ( "[2, 1, 4, null, null, 3]", bt_to_str( tree ) );
    }
}
