#include <limits>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    myAtoi( string str )
    {
        auto cit = str.begin( );
        while ( cit != str.end( ) && isspace( *cit ) )
        {
            ++cit;
        }

        bool negative = false;
        if ( cit != str.end( ) )
        {
            if ( *cit == '-' )
            {
                negative = true;
                ++cit;
            }
            else if ( *cit == '+' )
            {
                negative = false;
                ++cit;
            }
        }

        static const auto max_div_10 = numeric_limits< int >::max( ) / 10;
        int res = 0;
        while ( cit != str.end( ) && isdigit( *cit ) )
        {
            const int val = *cit++ - '0';
            if ( res > max_div_10 || ( res == max_div_10 && val >= 8 ) )
            {
                return negative ? numeric_limits< int >::min( ) : numeric_limits< int >::max( );
            }
            res = res * 10 + val;
        }

        return negative ? -res : res;
    }
};
}  // namespace

TEST( StringToInteger, generic )
{
    Solution sn;
    EXPECT_EQ( 42, sn.myAtoi( "42" ) );
    EXPECT_EQ( -42, sn.myAtoi( "   -42" ) );
    EXPECT_EQ( 4193, sn.myAtoi( "4193 with words" ) );
    EXPECT_EQ( 0, sn.myAtoi( "words and 987" ) );
    EXPECT_EQ( numeric_limits< int >::min( ), sn.myAtoi( "-91283472332" ) );
    EXPECT_EQ( numeric_limits< int >::max( ), sn.myAtoi( "2147483648" ) );
}
