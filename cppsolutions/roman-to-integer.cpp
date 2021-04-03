#include "gtest/gtest.h"

#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

namespace
{
class Solution
{
public:
    int
    romanToInt( string s )
    {
        static unordered_map< char, int > char_val{{'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50},
                                                   {'X', 10},   {'V', 5},   {'I', 1}};
        int prev_digit = numeric_limits< int >::max( );
        int res = 0;
        for ( auto const c : s )
        {
            auto digit = char_val[ c ];
            res += ( prev_digit < digit ) ? ( digit - 2 * prev_digit ) : digit;
            prev_digit = digit;
        }
        return res;
    }

private:
};
}  // namespace

TEST( RomanToInteger, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.romanToInt( "III" ) );
    EXPECT_EQ( 4, sn.romanToInt( "IV" ) );
    EXPECT_EQ( 9, sn.romanToInt( "IX" ) );
    EXPECT_EQ( 58, sn.romanToInt( "LVIII" ) );
    EXPECT_EQ( 1994, sn.romanToInt( "MCMXCIV" ) );
}
