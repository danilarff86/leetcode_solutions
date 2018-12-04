#include <cstdlib>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isOneEditDistance( string s, string t )
    {
        const int sz_diff = int( s.size( ) ) - int( t.size( ) );
        int i = 0;
        int j = 0;
        while ( i < s.size( ) && j < t.size( ) && s[ i ] == t[ j ] )
        {
            ++i;
            ++j;
        }

        i += sz_diff >= 0 ? 1 : 0;
        j += sz_diff <= 0 ? 1 : 0;

        while ( i < s.size( ) && j < t.size( ) && s[ i ] == t[ j ] )
        {
            ++i;
            ++j;
        }

        return i == s.size( ) && j == t.size( );
    }
};
}  // namespace

TEST(OneEditDistance, generic)
{
    Solution sn;
    EXPECT_TRUE( sn.isOneEditDistance( "ab", "acb" ) );
    EXPECT_FALSE( sn.isOneEditDistance( "cab", "ad" ) );
    EXPECT_TRUE( sn.isOneEditDistance( "1203", "1213" ) );
    EXPECT_FALSE( sn.isOneEditDistance( "", "" ) );
    EXPECT_TRUE( sn.isOneEditDistance( "a", "" ) );
    EXPECT_TRUE( sn.isOneEditDistance( "a", "ac" ) );
}