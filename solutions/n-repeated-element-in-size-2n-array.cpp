#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    repeatedNTimes( const vector< int >& A )
    {
        for ( size_t i = 2; i < A.size( ); i++ )
        {
            const auto elem = A[ i ];
            if ( elem == A[ i - 1 ] || elem == A[ i - 2 ] )
            {
                return elem;
            }
        }

        if ( A[ 0 ] == A[ 1 ] )
        {
            return A[ 0 ];
        }

        if ( A[ 0 ] == A[ A.size( ) - 1 ] )
        {
            return A[ 0 ];
        }

        return 0;
    }
};
}  // namespace

TEST( NRepeatedElementInSize2NArray, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.repeatedNTimes( {1, 2, 3, 3} ) );
    EXPECT_EQ( 2, sn.repeatedNTimes( {2, 1, 2, 5, 3, 2} ) );
    EXPECT_EQ( 5, sn.repeatedNTimes( {5, 1, 5, 2, 5, 3, 5, 4} ) );
    EXPECT_EQ( 3, sn.repeatedNTimes( {3, 1, 2, 3} ) );
}
