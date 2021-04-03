#include <queue>
#include "binary-tree.h"
#include "gtest/gtest.h"

using namespace std;
using namespace binary_tree;

namespace recursive
{
class Solution
{
public:
    bool
    isSymmetric( TreeNode* root )
    {
        return isMirrored( root, root );
    }

private:
    bool
    isMirrored( TreeNode* n1, TreeNode* n2 )
    {
        if ( n1 == nullptr && n2 == nullptr )
        {
            return true;
        }
        if ( n1 == nullptr || n2 == nullptr )
        {
            return false;
        }
        return ( n1->val == n2->val ) && isMirrored( n1->left, n2->right )
               && isMirrored( n1->right, n2->left );
    }
};
}  // namespace recursive

namespace iterative
{
class Solution
{
public:
    bool
    isSymmetric( TreeNode* root )
    {
        queue< TreeNode* > q;
        q.push( root );
        q.push( root );
        while ( !q.empty( ) )
        {
            auto n1 = q.front( );
            q.pop( );
            auto n2 = q.front( );
            q.pop( );

            if ( n1 == nullptr && n2 == nullptr )
            {
                continue;
            }

            if ( n1 == nullptr || n2 == nullptr || n1->val != n2->val )
            {
                return false;
            }

            q.push( n1->left );
            q.push( n2->right );
            q.push( n1->right );
            q.push( n2->left );
        }

        return true;
    }
};
}  // namespace iterative

TEST( SymmetricTree, generic )
{
    {
        recursive::Solution sn;
        EXPECT_TRUE( sn.isSymmetric( bt_from_str( "[1,2,2,3,4,4,3]" ) ) );
        EXPECT_FALSE( sn.isSymmetric( bt_from_str( "[1,2,2,null,3,null,3]" ) ) );
    }
    {
        iterative::Solution sn;
        EXPECT_TRUE( sn.isSymmetric( bt_from_str( "[1,2,2,3,4,4,3]" ) ) );
        EXPECT_FALSE( sn.isSymmetric( bt_from_str( "[1,2,2,null,3,null,3]" ) ) );
    }
}