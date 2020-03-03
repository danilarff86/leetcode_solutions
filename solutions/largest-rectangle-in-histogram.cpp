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

TEST( LargestRectangleInHistogram, generic )
{
    Solution sn;
    EXPECT_EQ( 10, sn.largestRectangleArea( {2, 1, 5, 6, 2, 3} ) );
    EXPECT_EQ( 6, sn.largestRectangleArea( {2, 1, 2, 4, 1, 3} ) );
}
