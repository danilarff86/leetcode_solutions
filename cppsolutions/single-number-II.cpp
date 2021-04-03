#include "gtest/gtest.h"

#include <vector>

using namespace std;

namespace
{
class Solution_straightforward
{
public:
    int
    singleNumber( const vector< int >& nums )
    {
        unsigned int bit_count[ 32 ]{};
        int result = 0;
        for ( size_t i_bit = 0; i_bit < 32; ++i_bit )
        {
            for ( const auto num : nums )
            {
                if ( ( num >> i_bit ) & 1 )
                {
                    ++bit_count[ i_bit ];
                }
            }
            result |= ( bit_count[ i_bit ] % 3 ) << i_bit;
        }
        return result;
    }
};

class Solution
{
public:
    int
    singleNumber( const vector< int >& nums )
    {
        int ones = 0, twos = 0, threes = 0;
        for ( const auto num : nums )
        {
            twos |= ones & num;
            ones ^= num;
            threes = ones & twos;
            ones &= ~threes;
            twos &= ~threes;
        }
        return ones;
    }
};
}  // namespace

TEST( SingleNumberII, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.singleNumber( {2, 2, 3, 2} ) );
    EXPECT_EQ( 99, sn.singleNumber( {0, 1, 0, 1, 0, 1, 99} ) );
}
