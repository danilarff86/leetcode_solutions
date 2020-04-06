#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    void
    rotate( vector< int >& nums, int k )
    {
        const auto sz = nums.size( );
        k = sz - ( k % sz );
        size_t start_index = 0;
        size_t next_index = 0;
        size_t step = 0;
        int tmp = nums[ start_index ];
        while ( step++ < sz )
        {
            const auto prev_index = next_index;

            next_index += k;
            if ( next_index >= sz )
            {
                next_index -= sz;
            }
            if ( next_index == start_index )
            {
                nums[ prev_index ] = tmp;
                if ( ++next_index >= sz )
                {
                    next_index = 0;
                }
                start_index = next_index;
                tmp = nums[ start_index ];
            }
            else
            {
                nums[ prev_index ] = nums[ next_index ];
            }
        }
    }
};

class Solution_Interview
{
public:
    template < typename T >
    void
    rotateArray( T* data, size_t N, size_t M )
    {
        M += 1;
        size_t start_index = 0;
        size_t next_index = 0;
        int tmp = data[ start_index ];
        for ( int i = 0; i < N; ++i )
        {
            const auto prev_index = next_index;
            next_index += M;
            if ( next_index >= N )
            {
                next_index -= N;
            }
            if ( next_index == start_index )
            {
                data[ prev_index ] = tmp;
                if ( ++next_index >= N )
                {
                    next_index = 0;
                }
                start_index = next_index;
                tmp = data[ start_index ];
            }
            else
            {
                data[ prev_index ] = data[ next_index ];
            }
        }
    }
};

vector< int >
rotate( Solution& sn, vector< int > nums, int k )
{
    sn.rotate( nums, k );
    return nums;
}

vector< int >
rotateArray( Solution_Interview& sn, vector< int > nums, int M )
{
    sn.rotateArray( nums.data( ), nums.size( ), M );
    return nums;
}
}  // namespace

TEST( RotateArray, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< int >{5, 6, 7, 1, 2, 3, 4} ), rotate( sn, {1, 2, 3, 4, 5, 6, 7}, 3 ) );
    EXPECT_EQ( ( vector< int >{3, 99, -1, -100} ), rotate( sn, {-1, -100, 3, 99}, 2 ) );
    EXPECT_EQ( ( vector< int >{-1} ), rotate( sn, {-1}, 2 ) );

    Solution_Interview sn_i;

    EXPECT_EQ( ( vector< int >{4, 5, 6, 7, 8, 1, 2, 3} ),
               rotateArray( sn_i, {1, 2, 3, 4, 5, 6, 7, 8}, 2 ) );
    EXPECT_EQ( ( vector< int >{3, 4, 5, 6, 7, 8, 1, 2} ),
               rotateArray( sn_i, {1, 2, 3, 4, 5, 6, 7, 8}, 1 ) );
    EXPECT_EQ( ( vector< int >{-1} ), rotateArray( sn_i, {-1}, 0 ) );
}
