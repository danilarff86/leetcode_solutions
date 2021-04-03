#include "gtest/gtest.h"

#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    spiralOrder( const vector< vector< int > >& matrix )
    {
        int row = 0, col = -1;
        int row_count = matrix.size( );
        if ( row_count == 0 )
        {
            return {};
        }

        int col_count = matrix[ 0 ].size( );
        vector< int > res;
        res.reserve( row_count * col_count );
        while ( true )
        {
            for ( int i = 0; i < col_count; ++i )
            {
                res.push_back( matrix[ row ][ ++col ] );
            }
            if ( --row_count == 0 )
            {
                break;
            }
            for ( int i = 0; i < row_count; ++i )
            {
                res.push_back( matrix[ ++row ][ col ] );
            }
            if ( --col_count == 0 )
            {
                break;
            }
            for ( int i = 0; i < col_count; ++i )
            {
                res.push_back( matrix[ row ][ --col ] );
            }
            if ( --row_count == 0 )
            {
                break;
            }
            for ( int i = 0; i < row_count; ++i )
            {
                res.push_back( matrix[ --row ][ col ] );
            }
            if ( --col_count == 0 )
            {
                break;
            }
        }
        return res;
    }
};
}  // namespace

TEST( SpiralMatrix, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {1, 2, 3, 6, 9, 8, 7, 4, 5} ),
               sn.spiralOrder( vector< vector< int > >{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} ) );
    EXPECT_EQ(
        vector< int >( {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7} ),
        sn.spiralOrder( vector< vector< int > >{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}} ) );
}
