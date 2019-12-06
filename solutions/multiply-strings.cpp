#include "gtest/gtest.h"

#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    string
    multiply( string num1, string num2 )
    {
        vector< int > buffer( num1.size( ) + num2.size( ) );
        for ( size_t i = 0; i < num1.size( ); i++ )
        {
            const auto d1 = num1[ num1.size( ) - i - 1 ] - '0';
            for ( size_t j = 0; j < num2.size( ); j++ )
            {
                const auto val = d1 * ( num2[ num2.size( ) - j - 1 ] - '0' );
                buffer[ buffer.size( ) - 1 - ( i + j ) ] += val;
            }
        }

        string result;
        result.resize( buffer.size( ) );

        int carry = 0;
        for ( int i = buffer.size( ) - 1; i >= 0; --i )
        {
            const auto val = buffer[ i ] + carry;
            carry = val / 10;

            result[ i ] = val - ( carry * 10 ) + '0';
        }

        int i = 0;
        while ( i < result.size( ) && result[ i ] == '0' )
        {
            ++i;
        }

        return i < result.size( ) ? result.substr( i ) : "0";
    }
};
}  // namespace

TEST( MultiplyStrings, generic )
{
    Solution sn;
    EXPECT_EQ( "6", sn.multiply( "2", "3" ) );
    EXPECT_EQ( "56088", sn.multiply( "123", "456" ) );
    EXPECT_EQ( "0", sn.multiply( "0", "0" ) );
    EXPECT_EQ( "998001", sn.multiply( "999", "999" ) );
}
