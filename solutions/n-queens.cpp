#include "gtest/gtest.h"

#include <string>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    vector< vector< string > >
    solveNQueens( int n )
    {
        board = vector< string >( n, string( n, '.' ) );
        col = vector< bool >( n );
        diagonal_1 = vector< bool >( n * 2 - 1 );
        diagonal_2 = vector< bool >( n * 2 - 1 );

        res.clear( );
        solve( 0 );
        return res;
    }

    void
    solve( size_t i_row )
    {
        if ( i_row == col.size( ) )
        {
            res.push_back( board );
            return;
        }

        for ( size_t i_col = 0; i_col < col.size( ); i_col++ )
        {
            if ( !col[ i_col ] && !diagonal_1[ diag_1_idx( i_row, i_col ) ]
                 && !diagonal_2[ diag_2_idx( i_row, i_col ) ] )
            {
                col[ i_col ] = true;
                diagonal_1[ diag_1_idx( i_row, i_col ) ] = true;
                diagonal_2[ diag_2_idx( i_row, i_col ) ] = true;
                board[ i_row ][ i_col ] = 'Q';

                solve( i_row + 1 );

                board[ i_row ][ i_col ] = '.';
                col[ i_col ] = false;
                diagonal_1[ diag_1_idx( i_row, i_col ) ] = false;
                diagonal_2[ diag_2_idx( i_row, i_col ) ] = false;
            }
        }
    }

    inline size_t
    diag_1_idx( size_t i_row, size_t i_col ) const
    {
        return i_row + i_col;
    }

    inline size_t
    diag_2_idx( size_t i_row, size_t i_col ) const
    {
        return ( col.size( ) - 1 - i_row ) + i_col;
    }

private:
    vector< string > board;
    vector< bool > col;
    vector< bool > diagonal_1;
    vector< bool > diagonal_2;

    vector< vector< string > > res;
};
}  // namespace

TEST( NQueens, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< vector< string > >{{".Q..", "...Q", "Q...", "..Q."},

                                            {"..Q.", "Q...", "...Q", ".Q.."}} ),
               sn.solveNQueens( 4 ) );
}
