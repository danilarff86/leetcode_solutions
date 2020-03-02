#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    double
    mincostToHireWorkers( const vector< int >& quality, const vector< int >& wage, int K )
    {
        const auto SZ = quality.size( );
        vector< double > ratio( SZ );
        vector< size_t > workers( SZ );

        for ( size_t i = 0; i < SZ; i++ )
        {
            ratio[ i ] = double( wage[ i ] ) / quality[ i ];
            workers[ i ] = i;
        }

        sort( workers.begin( ), workers.end( ),
              [&ratio]( size_t l, size_t r ) { return ratio[ l ] < ratio[ r ]; } );

        priority_queue< int > pq;
        int total_quality = 0;
        for ( size_t i = 0; i < K; i++ )
        {
            const auto worker_index = workers[ i ];
            pq.push( quality[ worker_index ] );
            total_quality += quality[ worker_index ];
        }
        auto res = total_quality * ratio[ workers[ K - 1 ] ];

        for ( size_t i = K; i < SZ; i++ )
        {
            const auto worker_index = workers[ i ];
            const auto worker_quality = quality[ worker_index ];

            pq.push( worker_quality );
            total_quality += worker_quality;
            total_quality -= pq.top( );
            pq.pop( );

            const auto local_res = total_quality * ratio[ worker_index ];
            if ( local_res < res )
            {
                res = local_res;
            }
        }

        return res;
    }
};
}  // namespace

TEST( MinimumCostToHireKWorkers, generic )
{
    Solution sn;
    EXPECT_DOUBLE_EQ( 105.0, sn.mincostToHireWorkers( {10, 20, 5}, {70, 50, 30}, 2 ) );
    EXPECT_DOUBLE_EQ( 30.666666666666664,
                      sn.mincostToHireWorkers( {3, 1, 10, 10, 1}, {4, 8, 2, 2, 7}, 3 ) );
    EXPECT_DOUBLE_EQ(
        1979.3142857142857,
        sn.mincostToHireWorkers( {25, 68, 35, 62, 52, 57, 35, 83, 40, 51},
                                 {147, 97, 251, 129, 438, 443, 120, 366, 362, 343}, 6 ) );
}
