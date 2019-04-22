#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maxWidthRamp( const vector< int >& A )
    {
        vector< int > indices( A.size( ) );
        int index = 0;
        generate( indices.begin( ), indices.end( ), [index]( ) mutable { return index++; } );
        stable_sort( indices.begin( ), indices.end( ),
                     [&A]( int l, int r ) { return A[ l ] < A[ r ]; } );

        int min_index = A.size( );
        int max_width_ramp = 0;
        for ( const auto index : indices )
        {
            max_width_ramp = max( max_width_ramp, index - min_index );
            min_index = min( min_index, index );
        }

        return max_width_ramp;
    }
};
}  // namespace

TEST( MaximumWidthRamp, generic )
{
    Solution sn;
    EXPECT_EQ( 4, sn.maxWidthRamp( {6, 0, 8, 2, 1, 5} ) );
    EXPECT_EQ( 7, sn.maxWidthRamp( {9, 8, 1, 0, 1, 9, 4, 0, 4, 1} ) );
    EXPECT_EQ( 25, sn.maxWidthRamp( {3,  28, 15, 1,  4, 12, 6, 19, 8, 15, 3, 9, 6, 4, 13,
                                     12, 6,  12, 10, 1, 2,  1, 4,  1, 4,  0, 0, 1, 1, 0} ) );
}
