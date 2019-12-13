#include <algorithm>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace recursive
{
class Solution
{
public:
    int
    largestIsland( const vector< vector< int > >& grid )
    {
        n_rows = grid.size( );
        n_cols = n_rows ? grid[ 0 ].size( ) : 0;
        traversed = vector< vector< int > >( n_rows, vector< int >( n_cols ) );
        grid_ptr = &grid;
        marker_val = 0;

        int res = 0;

        for ( size_t i = 0; i < n_rows; i++ )
        {
            for ( size_t j = 0; j < n_cols; j++ )
            {
                if ( grid[ i ][ j ] == 0 )
                {
                    ++marker_val;
                    res = max( calc_island( i, j ), res );
                }
            }
        }

        return res == 0 ? grid.size( ) * grid[ 0 ].size( ) : res;
    }

private:
    int
    calc_island( int i, int j )
    {
        int res = 1;
        traversed[ i ][ j ] = marker_val;

        if ( i > 0 && traversed[ i - 1 ][ j ] != marker_val && ( *grid_ptr )[ i - 1 ][ j ] )
        {
            res += calc_island( i - 1, j );
        }
        if ( ( i + 1 ) < n_rows && traversed[ i + 1 ][ j ] != marker_val
             && ( *grid_ptr )[ i + 1 ][ j ] )
        {
            res += calc_island( i + 1, j );
        }
        if ( j > 0 && traversed[ i ][ j - 1 ] != marker_val && ( *grid_ptr )[ i ][ j - 1 ] )
        {
            res += calc_island( i, j - 1 );
        }
        if ( ( j + 1 ) < n_rows && traversed[ i ][ j + 1 ] != marker_val
             && ( *grid_ptr )[ i ][ j + 1 ] )
        {
            res += calc_island( i, j + 1 );
        }

        return res;
    };

private:
    int n_rows;
    int n_cols;
    vector< vector< int > > traversed;
    const vector< vector< int > >* grid_ptr;
    int marker_val;
};
}  // namespace recursive
}  // namespace

TEST( MakingALargeIsland, generic )
{
    recursive::Solution sn;
    EXPECT_EQ( 3, sn.largestIsland( {{1, 0}, {0, 1}} ) );
    EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 0}} ) );
    EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 1}} ) );
}
