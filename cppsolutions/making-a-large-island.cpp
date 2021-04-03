#include <algorithm>
#include <functional>
#include <stack>
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
namespace island_info
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

        vector< int > islands_info( n_rows * n_cols / 2 + 2 );

        for ( size_t i = 0; i < n_rows; i++ )
        {
            for ( size_t j = 0; j < n_cols; j++ )
            {
                if ( grid[ i ][ j ] == 1 && traversed[ i ][ j ] == 0 )
                {
                    ++marker_val;
                    islands_info[ marker_val ] = calc_island( i, j );
                }
            }
        }

        for ( size_t i = 0; i < n_rows; i++ )
        {
            for ( size_t j = 0; j < n_cols; j++ )
            {
                if ( grid[ i ][ j ] == 0 )
                {
                    int islands[ 4 ]{};

                    if ( i > 0 )
                    {
                        islands[ 0 ] = traversed[ i - 1 ][ j ];
                    }
                    if ( ( i + 1 ) < n_rows )
                    {
                        auto const island_index = traversed[ i + 1 ][ j ];
                        if ( island_index != islands[ 0 ] )
                        {
                            islands[ 1 ] = island_index;
                        }
                    }
                    if ( j > 0 )
                    {
                        auto const island_index = traversed[ i ][ j - 1 ];
                        if ( island_index != islands[ 0 ] && island_index != islands[ 1 ] )
                        {
                            islands[ 2 ] = island_index;
                        }
                    }
                    if ( ( j + 1 ) < n_cols )
                    {
                        auto const island_index = traversed[ i ][ j + 1 ];
                        if ( island_index != islands[ 0 ] && island_index != islands[ 1 ]
                             && island_index != islands[ 2 ] )
                        {
                            islands[ 3 ] = island_index;
                        }
                    }

                    int local_res = 1;
                    for ( auto it = islands; it != islands + 4; ++it )
                    {
                        local_res += islands_info[ *it ];
                    }

                    res = max( res, local_res );
                }
            }
        }

        return res == 0 ? grid.size( ) * grid[ 0 ].size( ) : res;
    }

private:
    int
    calc_island( int i, int j )
    {
        stack< pair< int, int > > path;

        path.push( {i, j} );

        int res = 0;

        while ( !path.empty( ) )
        {
            i = path.top( ).first;
            j = path.top( ).second;
            path.pop( );

            if ( traversed[ i ][ j ] != marker_val )
            {
                res += 1;
                traversed[ i ][ j ] = marker_val;
            }

            if ( i > 0 && traversed[ i - 1 ][ j ] != marker_val && ( *grid_ptr )[ i - 1 ][ j ] )
            {
                path.push( {i - 1, j} );
            }
            if ( ( i + 1 ) < n_rows && traversed[ i + 1 ][ j ] != marker_val
                 && ( *grid_ptr )[ i + 1 ][ j ] )
            {
                path.push( {i + 1, j} );
            }
            if ( j > 0 && traversed[ i ][ j - 1 ] != marker_val && ( *grid_ptr )[ i ][ j - 1 ] )
            {
                path.push( {i, j - 1} );
            }
            if ( ( j + 1 ) < n_cols && traversed[ i ][ j + 1 ] != marker_val
                 && ( *grid_ptr )[ i ][ j + 1 ] )
            {
                path.push( {i, j + 1} );
            }
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
}  // namespace island_info
}  // namespace

TEST( MakingALargeIsland, generic )
{
    {
        recursive::Solution sn;
        EXPECT_EQ( 3, sn.largestIsland( {{1, 0}, {0, 1}} ) );
        EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 0}} ) );
        EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 1}} ) );
        EXPECT_EQ( 1, sn.largestIsland( {{1}} ) );
    }
    {
        island_info::Solution sn;
        EXPECT_EQ( 3, sn.largestIsland( {{1, 0}, {0, 1}} ) );
        EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 0}} ) );
        EXPECT_EQ( 4, sn.largestIsland( {{1, 1}, {1, 1}} ) );
        EXPECT_EQ( 1, sn.largestIsland( {{1}} ) );
    }
}
