#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace recursive
{
class Solution
{
public:
    int
    numDecodings( const string& s )
    {
        return recursive( s.c_str( ), s.size( ) );
    }

    int
    recursive( const char* str, int len )
    {
        if ( len == 0 )
        {
            return 1;
        }

        int res = str[ 0 ] != '0' ? recursive( str + 1, len - 1 ) : 0;

        if ( len > 1 && ( str[ 0 ] == '1' || ( str[ 0 ] == '2' && str[ 1 ] <= '6' ) ) )
        {
            res += recursive( str + 2, len - 2 );
        }

        return res;
    }
};
}  // namespace recursive

namespace dp
{
class Solution
{
public:
    int
    numDecodings( const string& s )
    {
        const int sz = s.size( );
        vector< int > dp( sz + 1 );

        dp[ sz ] = 1;
        dp[ sz - 1 ] = s[ sz - 1 ] != '0' ? 1 : 0;

        for ( int i = sz - 2; i >= 0; --i )
        {
            if ( s[ i ] != '0' )
            {
                dp[ i ] += dp[ i + 1 ];

                if ( s[ i ] == '1' || ( s[ i ] == '2' && s[ i + 1 ] <= '6' ) )
                {
                    dp[ i ] += dp[ i + 2 ];
                }
            }
        }

        return dp[ 0 ];
    }
};
}  // namespace dp
}  // namespace

TEST( DecodeWays, generic )
{
    {
        recursive::Solution sn;
        EXPECT_EQ( 2, sn.numDecodings( "12" ) );
        EXPECT_EQ( 3, sn.numDecodings( "226" ) );
        EXPECT_EQ( 0, sn.numDecodings( "0" ) );
        EXPECT_EQ( 0, sn.numDecodings( "00" ) );
    }

    {
        dp::Solution sn;
        EXPECT_EQ( 2, sn.numDecodings( "12" ) );
        EXPECT_EQ( 3, sn.numDecodings( "226" ) );
        EXPECT_EQ( 0, sn.numDecodings( "0" ) );
        EXPECT_EQ( 0, sn.numDecodings( "00" ) );
    }
}
