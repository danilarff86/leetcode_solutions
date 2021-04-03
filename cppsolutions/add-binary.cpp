#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

namespace
{
class Solution
{
public:
    string
    addBinary( string a, string b )
    {
        auto* shortest = &a;
        auto* longest = &b;
        if ( a.size( ) > b.size( ) )
        {
            std::swap( shortest, longest );
        }

        int carry = 0;
        const auto sz_diff = longest->size( ) - shortest->size( );

        for ( int i = shortest->size( ) - 1; i >= 0; --i )
        {
            const auto sum = ( *shortest )[ i ] - '0' + ( *longest )[ i + sz_diff ] - '0' + carry;
            ( *longest )[ i + sz_diff ] = sum & 1 ? '1' : '0';
            carry = sum > 1;
        }

        for ( int i = longest->size( ) - 1 - shortest->size( ); i >= 0; --i )
        {
            if ( carry )
            {
                if ( ( *longest )[ i ] == '1' )
                {
                    ( *longest )[ i ] = '0';
                }
                else
                {
                    ( *longest )[ i ] = '1';
                    carry = 0;
                    break;
                }
            }
            else
            {
                break;
            }
        }

        return carry ? "1" + *longest : *longest;
    }
};
}  // namespace

TEST( AddBinary, generic )
{
    Solution sn;
    EXPECT_EQ( "100", sn.addBinary( "11", "1" ) );
    EXPECT_EQ( "10101", sn.addBinary( "1010", "1011" ) );
    EXPECT_EQ( "110001", sn.addBinary( "101111", "10" ) );
}
