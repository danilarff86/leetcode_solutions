#include "gtest/gtest.h"

#include <string>

using namespace std;

namespace
{
class Solution
{
public:
    string
    intToRoman( int num )
    {
        string res;
        static const string symbols[]
            = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        static const int values[]{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        static const int num_values = sizeof( values ) / sizeof( values[ 0 ] );
        for ( int i = 0; i < num_values; ++i )
        {
            const auto& val = values[ i ];
            const auto& sym = symbols[ i ];
            while ( num >= val )
            {
                res.append( sym );
                num -= val;
            }
        }
        return res;
    }
};
}  // namespace

TEST( IntegerToRoman, generic )
{
    Solution sn;
    EXPECT_EQ( "III", sn.intToRoman( 3 ) );
    EXPECT_EQ( "IV", sn.intToRoman( 4 ) );
    EXPECT_EQ( "IX", sn.intToRoman( 9 ) );
    EXPECT_EQ( "LVIII", sn.intToRoman( 58 ) );
}
