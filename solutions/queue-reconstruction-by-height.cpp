#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    vector< vector< int > >
    reconstructQueue( vector< vector< int > >& people )
    {
        std::sort( people.begin( ), people.end( ),
                   []( const vector< int >& lhs, const vector< int >& rhs ) {
                       return lhs[ 0 ] == rhs[ 0 ] ? lhs[ 1 ] < rhs[ 1 ] : lhs[ 0 ] > rhs[ 0 ];
                   } );

        vector< vector< int > > res;
        res.reserve( people.size( ) );

        for ( auto& p : people )
        {
            const auto pos = next( res.begin( ), p[ 1 ] );
            res.insert( pos, std::move( p ) );
        }
        return res;
    }
};
}  // namespace

TEST( QueueReconstructionByHeight, generic )
{
    Solution sn;
    vector< vector< int > > expected{{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}};
    vector< vector< int > > origin{{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
    EXPECT_EQ( expected, sn.reconstructQueue( origin ) );
}
