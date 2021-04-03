#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    rotateString( string A, string B )
    {
        if ( A.size( ) != B.size( ) )
        {
            return false;
        }

        for ( size_t offset = 0; offset < B.size( ); offset++ )
        {
            size_t i_a = 0;
            size_t i_b = offset;
            for ( ; i_a < A.size( ); ++i_a )
            {
                if ( A[ i_a ] != B[ i_b ] )
                {
                    break;
                }
                if ( ++i_b >= B.size( ) )
                {
                    i_b = 0;
                }
            }
            if ( i_a == B.size( ) )
            {
                return true;
            }
        }

        return A.empty( );
    }
};
}  // namespace

TEST( RotateString, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.rotateString( "abcde", "cdeab" ) );
    EXPECT_FALSE( sn.rotateString( "abcde", "abced" ) );
    EXPECT_TRUE( sn.rotateString( "", "" ) );
    EXPECT_FALSE( sn.rotateString( "", "a" ) );
    EXPECT_FALSE( sn.rotateString( "ab", "a" ) );
}
