#include <queue>
#include <stack>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace bfs
{
class Solution
{
public:
    bool
    canVisitAllRooms( const vector< vector< int > >& rooms )
    {
        vector< bool > opened( rooms.size( ) );
        opened[ 0 ] = true;
        int rooms_opened = 1;
        queue< int > q;
        q.push( 0 );
        while ( !q.empty( ) )
        {
            const auto r = q.front( );
            q.pop( );

            for ( const auto k : rooms[ r ] )
            {
                if ( !opened[ k ] )
                {
                    q.push( k );
                    opened[ k ] = true;
                    ++rooms_opened;
                }
            }
        }

        return rooms_opened == rooms.size( );
    }
};
}  // namespace bfs
namespace dfs
{
class Solution
{
public:
    bool
    canVisitAllRooms( const vector< vector< int > >& rooms )
    {
        vector< bool > opened( rooms.size( ) );
        opened[ 0 ] = true;
        int rooms_opened = 1;
        stack< int > st;
        st.push( 0 );
        while ( !st.empty( ) )
        {
            const auto r = st.top( );
            st.pop( );

            for ( const auto k : rooms[ r ] )
            {
                if ( !opened[ k ] )
                {
                    st.push( k );
                    opened[ k ] = true;
                    ++rooms_opened;
                }
            }
        }

        return rooms_opened == rooms.size( );
    }
};
}  // namespace dfs
}  // namespace

TEST( KeysAndRooms, generic )
{
    {
        bfs::Solution sn;
        EXPECT_TRUE( sn.canVisitAllRooms( {{1}, {2}, {3}, {}} ) );
        EXPECT_FALSE( sn.canVisitAllRooms( {{1, 3}, {3, 0, 1}, {2}, {0}} ) );
    }
    {
        dfs::Solution sn;
        EXPECT_TRUE( sn.canVisitAllRooms( {{1}, {2}, {3}, {}} ) );
        EXPECT_FALSE( sn.canVisitAllRooms( {{1, 3}, {3, 0, 1}, {2}, {0}} ) );
    }
}
