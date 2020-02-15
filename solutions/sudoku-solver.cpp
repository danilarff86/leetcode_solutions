#include <algorithm>
#include <bitset>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
private:
    static const uint8_t DIGITS = 9;
    static const uint8_t DIGITS_SQRT = 3;
    static const char EMPTY_CELL = '.';
    static const char CHAR_OFFSET = '0';

    using DigitsInfo = bitset< DIGITS + 1 >;
    struct Position
    {
        size_t row;
        size_t col;
        Position( )
            : row( 0 )
            , col( 0 )
        {
        }
        bool
        is_done( ) const
        {
            return row == DIGITS;
        }
        void
        next( )
        {
            if ( ++col == DIGITS )
            {
                col = 0;
                ++row;
            }
        }
        Position
        iterated_clone( ) const
        {
            auto pos = *this;
            pos.next( );
            return pos;
        }
    };

public:
    void
    solveSudoku( vector< vector< char > >& board )
    {
        init_board_info( board );
        solveRecursive( board, {} );
    }

public:
    Solution( )
        : row_digits( DIGITS )
        , col_digits( DIGITS )
        , box_digits( DIGITS )
    {
    }

private:
    bool
    solveRecursive( vector< vector< char > >& board, Position pos )
    {
        while ( !pos.is_done( ) && board[ pos.row ][ pos.col ] != EMPTY_CELL )
        {
            pos.next( );
        }

        if ( pos.is_done( ) )
        {
            return true;
        }

        const auto i_box = get_box( pos.row, pos.col );
        for ( uint16_t digit = 1; digit <= DIGITS; digit++ )
        {
            if ( !box_digits[ i_box ].test( digit ) && !row_digits[ pos.row ].test( digit )
                 && !col_digits[ pos.col ].test( digit ) )
            {
                box_digits[ i_box ].set( digit );
                row_digits[ pos.row ].set( digit );
                col_digits[ pos.col ].set( digit );
                board[ pos.row ][ pos.col ] = CHAR_OFFSET + digit;

                if ( solveRecursive( board, pos.iterated_clone( ) ) )
                {
                    return true;
                }

                board[ pos.row ][ pos.col ] = EMPTY_CELL;

                box_digits[ i_box ].reset( digit );
                row_digits[ pos.row ].reset( digit );
                col_digits[ pos.col ].reset( digit );
            }
        }

        return false;
    }

    void
    init_board_info( vector< vector< char > >& board )
    {
        for_each( row_digits.begin( ), row_digits.end( ), []( DigitsInfo& bs ) { bs.reset( ); } );
        for_each( col_digits.begin( ), col_digits.end( ), []( DigitsInfo& bs ) { bs.reset( ); } );
        for_each( box_digits.begin( ), box_digits.end( ), []( DigitsInfo& bs ) { bs.reset( ); } );

        for ( size_t i_row = 0; i_row < DIGITS; i_row++ )
        {
            for ( size_t i_col = 0; i_col < DIGITS; i_col++ )
            {
                const auto c = board[ i_row ][ i_col ];
                if ( c != EMPTY_CELL )
                {
                    const auto digit = c - CHAR_OFFSET;
                    box_digits[ get_box( i_row, i_col ) ].set( digit );
                    row_digits[ i_row ].set( digit );
                    col_digits[ i_col ].set( digit );
                }
            }
        }
    }

    static inline size_t
    get_box( size_t row, size_t col )
    {
        return row / DIGITS_SQRT * DIGITS_SQRT + col / DIGITS_SQRT;
    }

private:
    vector< DigitsInfo > row_digits;
    vector< DigitsInfo > col_digits;
    vector< DigitsInfo > box_digits;
};
}  // namespace

TEST( SudokuSolver, generic )
{
    vector< vector< char > > board{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                   {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                   {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                   {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                   {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                   {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                   {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                   {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                   {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    ;
    Solution sn;
    sn.solveSudoku( board );
    EXPECT_EQ( ( vector< vector< char > >{{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
                                          {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
                                          {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
                                          {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
                                          {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
                                          {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
                                          {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
                                          {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
                                          {'3', '4', '5', '2', '8', '6', '1', '7', '9'}} ),
               board );
}
