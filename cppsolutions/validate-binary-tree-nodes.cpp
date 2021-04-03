#include <queue>
#include <stack>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    validateBinaryTreeNodes( int n,
                             const vector< int >& leftChild,
                             const vector< int >& rightChild )
    {
        vector< bool > traversed( n );
        size_t traversed_count = 0;
        stack< int > st;
        st.push( 0 );
        while ( !st.empty( ) )
        {
            const auto node = st.top( );
            st.pop( );

            if ( node == -1 )
            {
                continue;
            }

            if ( traversed[ node ] )
            {
                return false;
            }

            traversed[ node ] = true;
            ++traversed_count;

            st.push( leftChild[ node ] );
            st.push( rightChild[ node ] );
        }

        return traversed_count == n;
    }
};
}  // namespace

TEST( ValidateBinaryTreeNodes, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.validateBinaryTreeNodes( 4, {1, -1, 3, -1}, {2, -1, -1, -1} ) );
    EXPECT_FALSE( sn.validateBinaryTreeNodes( 4, {1, -1, 3, -1}, {2, 3, -1, -1} ) );
    EXPECT_FALSE( sn.validateBinaryTreeNodes( 2, {1, 0}, {-1, -1} ) );
    EXPECT_FALSE( sn.validateBinaryTreeNodes( 6, {1, -1, -1, 4, -1, -1}, {2, -1, -1, 5, -1, -1} ) );
    EXPECT_FALSE( sn.validateBinaryTreeNodes( 5, {2, 2, -1, 1, 3}, {2, 2, 1, 2, 1} ) );
}
