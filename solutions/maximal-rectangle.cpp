#include "gtest/gtest.h"

#include <stack>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    maximalRectangle( const vector< vector< char > >& matrix )
    {
        const auto ROWS = matrix.size( );
        const auto COLS = matrix.empty( ) ? 0u : matrix[ 0 ].size( );
        vector< vector< int > > dp( ROWS, vector< int >( COLS ) );
        for ( size_t j = 0; j < COLS; j++ )
        {
            dp[ 0 ][ j ] = matrix[ 0 ][ j ] - '0';
        }
        for ( size_t i = 1; i < ROWS; i++ )
        {
            for ( size_t j = 0; j < COLS; j++ )
            {
                int val = matrix[ i ][ j ] - '0';
                if ( val == 1 )
                {
                    val += dp[ i - 1 ][ j ];
                }
                dp[ i ][ j ] = val;
            }
        }

        int res = 0;
        for ( const auto& dp_row : dp )
        {
            const auto local_res = largestRectangleArea( dp_row );
            if ( local_res > res )
            {
                res = local_res;
            }
        }
        return res;
    }

private:
    int
    largestRectangleArea( const vector< int >& heights )
    {
        stack< int > s;
        s.push( -1 );
        int res = 0;
        for ( int i = 0; i < heights.size( ); i++ )
        {
            while ( s.size( ) > 1 && ( heights[ i ] < heights[ s.top( ) ] ) )
            {
                const auto cur = s.top( );
                s.pop( );
                int area = heights[ cur ] * ( i - 1 - s.top( ) );
                if ( area > res )
                {
                    res = area;
                }
            }
            s.push( i );
        }

        while ( s.size( ) > 1 )
        {
            const auto cur = s.top( );
            s.pop( );
            int area = heights[ cur ] * ( heights.size( ) - 1 - s.top( ) );
            if ( area > res )
            {
                res = area;
            }
        }

        return res;
    }
};
}  // namespace

TEST( MaximalRectangle, generic )
{
    Solution sn;
    EXPECT_EQ( 6, sn.maximalRectangle( {{'1', '0', '1', '0', '0'},
                                        {'1', '0', '1', '1', '1'},
                                        {'1', '1', '1', '1', '1'},
                                        {'1', '0', '0', '1', '0'}} ) );
}
