#include "binary_tree.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <unordered_set>

using namespace std;
using namespace binary_tree;

namespace
{
class Solution_dp
{
public:
    struct Counters
    {
        inline int
        min_covered( ) const
        {
            return min( covered_with_camera, covered_without_camera );
        }

        int not_covered;
        int covered_without_camera;
        int covered_with_camera;
    };

    int
    minCameraCover( TreeNode* root )
    {
        return solve( root ).min_covered( );
    }

private:
    Counters
    solve( TreeNode* node )
    {
        if ( node == nullptr )
        {
            return {0, 0, 99999};
        }

        const auto l_cnt = solve( node->left );
        const auto r_cnt = solve( node->right );
        const auto l_cov_min = l_cnt.min_covered( );
        const auto r_cov_min = r_cnt.min_covered( );

        Counters counters;
        counters.not_covered = l_cnt.covered_without_camera + r_cnt.covered_without_camera;
        counters.covered_without_camera = min( ( l_cnt.covered_with_camera + r_cov_min ),
                                               ( r_cnt.covered_with_camera + l_cov_min ) );
        counters.covered_with_camera
            = 1 + min( l_cnt.not_covered, l_cov_min ) + min( r_cnt.not_covered, r_cov_min );

        return counters;
    }
};

class Solution
{
public:
    int
    minCameraCover( TreeNode* root )
    {
        cameras = 0;
        covered.clear( );
        covered.insert( nullptr );
        dfs( root, nullptr );
        return cameras;
    }

private:
    void
    dfs( TreeNode* node, TreeNode* parent )
    {
        if ( node != nullptr )
        {
            dfs( node->left, node );
            dfs( node->right, node );

            if ( ( parent == nullptr && covered.count( node ) == 0 )
                 || covered.count( node->left ) == 0 || covered.count( node->right ) == 0 )
            {
                ++cameras;
                covered.insert( node );
                covered.insert( parent );
                covered.insert( node->left );
                covered.insert( node->right );
            }
        }
    }

private:
    unordered_set< const TreeNode* > covered;
    int cameras;
};

}  // namespace

TEST( BinaryTreeCameras, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.minCameraCover( bt_from_str( "[0,0,null,0,0]" ) ) );
    EXPECT_EQ( 2, sn.minCameraCover( bt_from_str( "[0,0,null,0,null,0,null,null,0]" ) ) );
    EXPECT_EQ( 1, sn.minCameraCover( bt_from_str( "[0]" ) ) );
    EXPECT_EQ( 1, sn.minCameraCover( bt_from_str( "[0,0,0]" ) ) );
    EXPECT_EQ( 2, sn.minCameraCover( bt_from_str( "[0,null,0,null,0,null,0]" ) ) );
}
