#include <array>
#include <cstdint>
#include <queue>
#include <unordered_set>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    using Board = array< array< uint8_t, 3 >, 2 >;

    struct BoardInfo
    {
        Board board;
        uint16_t depth;
        pair< uint8_t, uint8_t > zero_pos;
    };

    int
    slidingPuzzle( const vector< vector< int > >& board )
    {
        // static const uint32_t MAX_DEPTH = 720;
        static const auto result_board_hash
            = board_hash( Board{Board::value_type{1, 2, 3}, Board::value_type{4, 5, 0}} );

        traversed.clear( );

        queue< BoardInfo > q;
        q.push( BoardInfo{
            {Board::value_type{static_cast< Board::value_type::value_type >( board[ 0 ][ 0 ] ),
                               static_cast< Board::value_type::value_type >( board[ 0 ][ 1 ] ),
                               static_cast< Board::value_type::value_type >( board[ 0 ][ 2 ] )},
             Board::value_type{static_cast< Board::value_type::value_type >( board[ 1 ][ 0 ] ),
                               static_cast< Board::value_type::value_type >( board[ 1 ][ 1 ] ),
                               static_cast< Board::value_type::value_type >( board[ 1 ][ 2 ] )}},
            0,
            {0, 0}} );
        auto& initial = q.front( ).board;
        for ( size_t i = 0; i < 2; i++ )
        {
            for ( size_t j = 0; j < 3; j++ )
            {
                if ( initial[ i ][ j ] == 0 )
                {
                    q.front( ).zero_pos = {i, j};
                }
            }
        }

        traversed.insert( board_hash( q.front( ).board ) );

        while ( !q.empty( ) )
        {
            const auto board_info = q.front( );
            q.pop( );

            if ( board_hash( board_info.board ) == result_board_hash )
            {
                return board_info.depth;
            }

            const uint16_t next_depth = board_info.depth + 1;

            if ( board_info.zero_pos.second > 0 )
            {
                Board b = board_info.board;
                swap( b[ board_info.zero_pos.first ][ board_info.zero_pos.second ],
                      b[ board_info.zero_pos.first ][ board_info.zero_pos.second - 1 ] );
                if ( traversed.insert( board_hash( b ) ).second )
                {
                    q.push( {std::move( b ),
                             next_depth,
                             {board_info.zero_pos.first, board_info.zero_pos.second - 1}} );
                }
            }
            if ( board_info.zero_pos.second < 2 )
            {
                Board b = board_info.board;
                swap( b[ board_info.zero_pos.first ][ board_info.zero_pos.second ],
                      b[ board_info.zero_pos.first ][ board_info.zero_pos.second + 1 ] );
                if ( traversed.insert( board_hash( b ) ).second )
                {
                    q.push( {std::move( b ),
                             next_depth,
                             {board_info.zero_pos.first, board_info.zero_pos.second + 1}} );
                }
            }

            if ( board_info.zero_pos.first > 0 )
            {
                Board b = board_info.board;
                swap( b[ board_info.zero_pos.first ][ board_info.zero_pos.second ],
                      b[ board_info.zero_pos.first - 1 ][ board_info.zero_pos.second ] );
                if ( traversed.insert( board_hash( b ) ).second )
                {
                    q.push( {std::move( b ),
                             next_depth,
                             {board_info.zero_pos.first - 1, board_info.zero_pos.second}} );
                }
            }
            else
            {
                Board b = board_info.board;
                swap( b[ board_info.zero_pos.first ][ board_info.zero_pos.second ],
                      b[ board_info.zero_pos.first + 1 ][ board_info.zero_pos.second ] );
                if ( traversed.insert( board_hash( b ) ).second )
                {
                    q.push( {std::move( b ),
                             next_depth,
                             {board_info.zero_pos.first + 1, board_info.zero_pos.second}} );
                }
            }
        }

        return -1;
    }

private:
    unordered_set< uint32_t > traversed;

    static inline uint32_t
    board_hash( const Board& board )
    {
        return board[ 0 ][ 0 ] | ( board[ 0 ][ 1 ] << 3 ) | ( board[ 0 ][ 2 ] << 6 )
               | ( board[ 1 ][ 0 ] << 9 ) | ( board[ 1 ][ 1 ] << 12 ) | ( board[ 1 ][ 2 ] << 15 );
    }
};
}  // namespace

TEST( SlidingPuzzle, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.slidingPuzzle( {{1, 2, 3}, {4, 0, 5}} ) );
    EXPECT_EQ( -1, sn.slidingPuzzle( {{1, 2, 3}, {5, 4, 0}} ) );
    EXPECT_EQ( 5, sn.slidingPuzzle( {{4, 1, 2}, {5, 0, 3}} ) );
    EXPECT_EQ( 14, sn.slidingPuzzle( {{3, 2, 4}, {1, 5, 0}} ) );
}
