#include <algorithm>
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
    kClosest( vector< vector< int > >& points, int K )
    {
        const auto sz = points.size( );
        vector< int > squared_euclidean_distances( sz );
        std::transform( points.begin( ), points.end( ), squared_euclidean_distances.begin( ),
                        []( const vector< int >& v ) {
                            const auto q1 = v[ 0 ];
                            const auto q2 = v[ 1 ];
                            return q1 * q1 + q2 * q2;
                        } );

        auto comp = [&squared_euclidean_distances]( size_t lhs_index, size_t rhs_index ) {
            return squared_euclidean_distances[ lhs_index ]
                   > squared_euclidean_distances[ rhs_index ];
        };

        priority_queue< size_t, vector< size_t >, decltype( comp ) > indices_of_closest_points(
            comp );

        for ( size_t i = 0; i < sz; ++i )
        {
            indices_of_closest_points.push( i );
        }

        vector< vector< int > > res( K );

        for ( int i = 0; i < K; ++i )
        {
            res[ i ] = std::move( points[ indices_of_closest_points.top( ) ] );
            indices_of_closest_points.pop( );
        }

        return res;
    }
};
}  // namespace

TEST( KClosestPointsToOrigin, generic )
{
    Solution sn;
    {
        vector< vector< int > > points( {{1, 3}, {-2, 2}} );
        EXPECT_EQ( vector< vector< int > >( {{-2, 2}} ), sn.kClosest( points, 1 ) );
    }

    {
        vector< vector< int > > points( {{3, 3}, {5, -1}, {-2, 4}} );
        EXPECT_EQ( vector< vector< int > >( {{3, 3}, {-2, 4}} ), sn.kClosest( points, 2 ) );
    }
}
