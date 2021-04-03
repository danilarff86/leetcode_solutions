#include <climits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
struct meta
{
    int origin;
    int color;
    int hops;
};

class Solution
{
public:
    vector< int >
    shortestAlternatingPaths( int n,
                              const vector< vector< int > >& red_edges,
                              const vector< vector< int > >& blue_edges )
    {
        const vector< vector< int > >* edges[] = {&red_edges, &blue_edges};
        vector< int > res( n, -1 );
        res[ 0 ] = 0;

        queue< meta > q;

        for ( int color : {0, 1} )
        {
            vector< int > visited[] = {vector< int >( n ), vector< int >( n )};
            q.push( {0, color, 0} );

            while ( !q.empty( ) )
            {
                const auto v = q.front( );
                q.pop( );

                if ( visited[ v.color ][ v.origin ] )
                {
                    continue;
                }
                visited[ v.color ][ v.origin ] = 1;

                const auto next_color = v.color ^ 1;
                const auto hops = v.hops + 1;

                for ( const auto& edge : *( edges[ next_color ] ) )
                {
                    if ( v.origin == edge[ 0 ] )
                    {
                        const auto dest = edge[ 1 ];
                        q.push( {dest, next_color, hops} );
                        if ( res[ dest ] == -1 || res[ dest ] > hops )
                        {
                            res[ dest ] = hops;
                        }
                    }
                }
            }
        }

        return res;
    }
};
}  // namespace

TEST( ShortestPathWithAlternatingColors, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< int >{0, 1, -1} ),
               sn.shortestAlternatingPaths( 3, {{0, 1}, {1, 2}}, {} ) );
    EXPECT_EQ( ( vector< int >{0, 1, -1} ), sn.shortestAlternatingPaths( 3, {{0, 1}}, {{2, 1}} ) );
    EXPECT_EQ( ( vector< int >{0, -1, -1} ), sn.shortestAlternatingPaths( 3, {{1, 0}}, {{2, 1}} ) );
    EXPECT_EQ( ( vector< int >{0, 1, 2} ), sn.shortestAlternatingPaths( 3, {{0, 1}}, {{1, 2}} ) );
    EXPECT_EQ( ( vector< int >{0, 1, 1} ),
               sn.shortestAlternatingPaths( 3, {{0, 1}, {0, 2}}, {{1, 0}} ) );
}
