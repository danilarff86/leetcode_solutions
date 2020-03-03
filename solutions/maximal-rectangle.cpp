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
        vector< int > dp( COLS );
        for ( size_t j = 0; j < COLS; j++ )
        {
            dp[ j ] = matrix[ 0 ][ j ] - '0';
        }

        auto res = largestRectangleArea( dp );

        for ( size_t i = 1; i < ROWS; i++ )
        {
            for ( size_t j = 0; j < COLS; j++ )
            {
                if ( matrix[ i ][ j ] == '1' )
                {
                    ++dp[ j ];
                }
                else
                {
                    dp[ j ] = 0;
                }
            }
            const auto local_res = largestRectangleArea( dp );
            if ( local_res > res )
            {
                res = local_res;
            }
        }

        return res;
    }

private:
    static inline int
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
