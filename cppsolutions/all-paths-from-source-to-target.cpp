#include <queue>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< vector< int > >
    allPathsSourceTarget( const vector< vector< int > >& graph )
    {
        vector< vector< int > > res;
        const int last_node = graph.size( ) - 1;
        queue< vector< int > > q;
        q.push( {0} );
        while ( !q.empty( ) )
        {
            const auto& path = q.front( );
            for ( const auto& next_node : graph[ path.back( ) ] )
            {
                vector< int > new_path = path;
                new_path.push_back( next_node );
                if ( next_node == last_node )
                {
                    res.push_back( move( new_path ) );
                }
                else
                {
                    q.push( move( new_path ) );
                }
            }
            q.pop( );
        }
        return res;
    }
};
}  // namespace

TEST( AllPathsFromSourceToTarget, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< vector< int > >{{0, 1, 3}, {0, 2, 3}} ),
               sn.allPathsSourceTarget( {{1, 2}, {3}, {3}, {}} ) );
}
