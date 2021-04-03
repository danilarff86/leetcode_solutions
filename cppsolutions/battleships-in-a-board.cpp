#include "gtest/gtest.h"

#include <vector>

using namespace std;

namespace
{
vector< vector< char > >
convert_input_data( const vector< std::string >& input )
{
    vector< vector< char > > res;
    res.reserve( input.size( ) );
    for ( const auto& str : input )
    {
        res.push_back( vector< char >( str.begin( ), str.end( ) ) );
    }
    return res;
}
}  // namespace

namespace
{
class Solution
{
public:
    int
    countBattleships( const vector< vector< char > >& board )
    {
        const auto rows_count = board.size( );
        const auto cols_count = rows_count > 0 ? board[ 0 ].size( ) : 0;
        int res = 0;
        for ( size_t col = 0; col < cols_count; ++col )
        {
            if ( board[ 0 ][ col ] == 'X' )
            {
                ++res;
                ++col;
                while ( col < cols_count && board[ 0 ][ col ] == 'X' )
                {
                    ++col;
                }
            }
        }
        for ( size_t row = 1; row < rows_count; ++row )
        {
            for ( size_t col = 0; col < cols_count; ++col )
            {
                if ( board[ row ][ col ] == 'X' && board[ row - 1 ][ col ] != 'X' )
                {
                    ++res;
                    ++col;
                    while ( col < cols_count && board[ row ][ col ] == 'X' )
                    {
                        ++col;
                    }
                }
            }
        }
        return res;
    }
};
}  // namespace

TEST( BattleshipsInABoard, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.countBattleships( convert_input_data( {"X..X", "...X", "...X"} ) ) );
}
