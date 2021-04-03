#include <algorithm>
#include <array>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace with_string
{
class Solution
{
public:
    bool
    reorderedPowerOf2( int N )
    {
        auto s = to_string( N );
        sort( s.begin( ), s.end( ) );
        do
        {
            if ( s[ 0 ] != '0' && isPowerOf2( stoi( s ) ) )
            {
                return true;
            }
        } while ( next_permutation( s.begin( ), s.end( ) ) );

        return false;
    }

private:
    bool
    isPowerOf2( int N )
    {
        int bits_cnt = 0;
        int shift_cnt = 31;
        for ( uint32_t i = 0; i < 32; ++i )
        {
            bits_cnt += ( N >> i ) & 1;
        }
        return bits_cnt == 1;
    }
};
}  // namespace with_string
namespace count_number_of_digits
{
class Solution
{
public:
    bool
    reorderedPowerOf2( int N )
    {
        array< uint8_t, 10 > N_digits{};
        count_num_digits( N_digits, N );
        for ( uint32_t i = 0; i < 32; ++i )
        {
            array< uint8_t, 10 > pow_2_digits{};
            count_num_digits( pow_2_digits, 1 << i );
            if ( N_digits == pow_2_digits )
            {
                return true;
            }
        }

        return false;
    }

private:
    void count_num_digits( array< uint8_t, 10 >& digits, int N )
    {
        while ( N > 0 )
        {
            ++digits[ N % 10 ];
            N /= 10;
        }
    }
};
}  // namespace count_number_of_digits
}  // namespace

TEST( ReorderedPowerOf2, generic )
{
    {
        with_string::Solution sn;
        EXPECT_TRUE( sn.reorderedPowerOf2( 1 ) );
        EXPECT_FALSE( sn.reorderedPowerOf2( 10 ) );
        EXPECT_TRUE( sn.reorderedPowerOf2( 16 ) );
        EXPECT_FALSE( sn.reorderedPowerOf2( 24 ) );
        EXPECT_TRUE( sn.reorderedPowerOf2( 46 ) );
    }
    {
        count_number_of_digits::Solution sn;
        EXPECT_TRUE( sn.reorderedPowerOf2( 1 ) );
        EXPECT_FALSE( sn.reorderedPowerOf2( 10 ) );
        EXPECT_TRUE( sn.reorderedPowerOf2( 16 ) );
        EXPECT_FALSE( sn.reorderedPowerOf2( 24 ) );
        EXPECT_TRUE( sn.reorderedPowerOf2( 46 ) );
    }
}
