#include "gtest/gtest.h"

#include <deque>

using namespace std;

namespace
{
class Solution
{
public:
    int
    minKBitFlips( const vector< int >& A, int K )
    {
        const int max_flip_index = A.size( ) - K;

        vector< int > flip_indices( max_flip_index + 1 );
        auto flip_indices_begin = flip_indices.begin( );
        auto flip_indices_end = flip_indices.begin( );

        int result_size = 0;
        int i = 0;

        for ( ; i <= max_flip_index; ++i )
        {
            if ( ( flip_indices_begin != flip_indices_end ) && *flip_indices_begin + K <= i )
            {
                ++flip_indices_begin;
            }
            if ( !( ( ( flip_indices_end - flip_indices_begin ) + A[ i ] ) & 1 ) )
            {
                *flip_indices_end++ = i;
                ++result_size;
            }
        }

        for ( ; i < A.size( ); ++i )
        {
            if ( ( flip_indices_begin != flip_indices_end ) && *flip_indices_begin + K <= i )
            {
                ++flip_indices_begin;
            }
            if ( !( ( ( flip_indices_end - flip_indices_begin ) + A[ i ] ) & 1 ) )
            {
                return -1;
            }
        }

        return result_size;
    }
};
}  // namespace

TEST( MinimumNumberOfKConsecutiveBitFlips, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.minKBitFlips( {0, 1, 0}, 1 ) );
    EXPECT_EQ( -1, sn.minKBitFlips( {1, 1, 0}, 2 ) );
    EXPECT_EQ( 3, sn.minKBitFlips( {0, 0, 0, 1, 0, 1, 1, 0}, 3 ) );
}
