#include "gtest/gtest.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    smallestRangeII( vector< int >&& A, int K )
    {
        sort( A.begin( ), A.end( ) );

        const auto max_val = A.back( );
        const auto min_val = A.front( );

        const auto min_plus_2k = min_val + 2 * K;

        int res = max_val - min_val;

        for ( size_t i = 0; i < A.size( ) - 1; ++i )
        {
            const auto l = min( A[ i + 1 ], min_plus_2k );
            const auto h = max( A[ i ] + 2 * K, max_val );
            const auto diff = h - l;
            if ( diff < res )
            {
                res = diff;
            }
        }
        return res;
    }
};
}  // namespace

TEST( SmallestRangeII, generic )
{
    Solution sn;
    EXPECT_EQ( 0, sn.smallestRangeII( {1}, 0 ) );
    EXPECT_EQ( 6, sn.smallestRangeII( {0, 10}, 2 ) );
    EXPECT_EQ( 3, sn.smallestRangeII( {1, 3, 6}, 3 ) );
    EXPECT_EQ( 1, sn.smallestRangeII( {7, 8, 8}, 5 ) );
    EXPECT_EQ( 5, sn.smallestRangeII( {9, 10, 5, 9}, 5 ) );
    EXPECT_EQ( 7, sn.smallestRangeII( {3, 4, 7, 0}, 5 ) );
    EXPECT_EQ( 2, sn.smallestRangeII( {3, 1, 10}, 4 ) );
    EXPECT_EQ( 6, sn.smallestRangeII( {4, 8, 2, 7, 2}, 5 ) );
    EXPECT_EQ( 8870,
               sn.smallestRangeII(
                   {8038, 9111, 5458, 8483, 5052, 9161, 8368, 2094, 8366, 9164, 53,   7222, 9284,
                    5059, 4375, 2667, 2243, 5329, 3111, 5678, 5958, 815,  6841, 1377, 2752, 8569,
                    1483, 9191, 4675, 6230, 1169, 9833, 5366, 502,  1591, 5113, 2706, 8515, 3710,
                    7272, 1596, 5114, 3620, 2911, 8378, 8012, 4586, 9610, 8361, 1646, 2025, 1323,
                    5176, 1832, 7321, 1900, 1926, 5518, 8801, 679,  3368, 2086, 7486, 575,  9221,
                    2993, 421,  1202, 1845, 9767, 4533, 1505, 820,  967,  2811, 5603, 574,  6920,
                    5493, 9490, 9303, 4648, 281,  2947, 4117, 2848, 7395, 930,  1023, 1439, 8045,
                    5161, 2315, 5705, 7596, 5854, 1835, 6591, 2553, 8628},
                   4643 ) );

    EXPECT_EQ( 37, sn.smallestRangeII( {100, 50, 73, 79}, 30 ) );
}
