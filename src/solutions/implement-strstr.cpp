#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    strStr( string haystack, string needle )
    {
        int const sz_diff = haystack.size( ) - needle.size( );
        for ( int i = 0; i <= sz_diff; ++i )
        {
            int j = 0;
            while ( j < needle.size( ) && needle[ j ] == haystack[ i + j ] )
            {
                ++j;
            }
            if ( j == needle.size( ) )
            {
                return i;
            }
        }
        return -1;
    }
};
}  // namespace

TEST( ImplementStrStr, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.strStr( "hello", "ll" ) );
    EXPECT_EQ( -1, sn.strStr( "aaaaa", "bba" ) );
}