#include "gtest/gtest.h"

#include <cstdint>
#include <vector>

using namespace std;

namespace
{
namespace dp_article
{
class Solution
{
public:
    static const int M = 1000000007;
    int
    numDecodings( const string& s )
    {
        const int sz = s.size( );
        vector< uint64_t > dp( sz + 1 );
        dp[ 0 ] = 1;
        dp[ 1 ] = s[ 0 ] == '*' ? 9 : s[ 0 ] == '0' ? 0 : 1;
        for ( int i = 1; i < sz; i++ )
        {
            if ( s[ i ] == '*' )
            {
                dp[ i + 1 ] = 9 * dp[ i ];
                if ( s[ i - 1 ] == '1' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + 9 * dp[ i - 1 ] ) % M;
                }
                else if ( s[ i - 1 ] == '2' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + 6 * dp[ i - 1 ] ) % M;
                }
                else if ( s[ i - 1 ] == '*' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + 15 * dp[ i - 1 ] ) % M;
                }
            }
            else
            {
                dp[ i + 1 ] = s[ i ] != '0' ? dp[ i ] : 0;
                if ( s[ i - 1 ] == '1' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + dp[ i - 1 ] ) % M;
                }
                else if ( s[ i - 1 ] == '2' && s[ i ] <= '6' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + dp[ i - 1 ] ) % M;
                }
                else if ( s[ i - 1 ] == '*' )
                {
                    dp[ i + 1 ] = ( dp[ i + 1 ] + ( s[ i ] <= '6' ? 2 : 1 ) * dp[ i - 1 ] ) % M;
                }
            }
        }
        return dp[ sz ];
    }
};
}  // namespace dp_article

namespace dp_mine
{
class Solution
{
public:
    int
    numDecodings( const string& s )
    {
        const int sz = s.size( );
        vector< uint64_t > dp( sz + 1 );

        dp[ sz ] = 1;
        dp[ sz - 1 ] = s[ sz - 1 ] != '0' ? ( s[ sz - 1 ] == '*' ? 9 : 1 ) : 0;

        for ( int i = sz - 2; i >= 0; --i )
        {
            if ( s[ i ] != '0' )
            {
                if ( s[ i ] == '*' )
                {
                    dp[ i ] += dp[ i + 1 ] * 9;
                    if ( s[ i + 1 ] == '*' )
                    {
                        dp[ i ] += dp[ i + 2 ] * 15;
                    }
                    else if ( s[ i + 1 ] <= '6' )
                    {
                        dp[ i ] += dp[ i + 2 ] * 2;
                    }
                    else
                    {
                        dp[ i ] += dp[ i + 2 ];
                    }
                }
                else
                {
                    dp[ i ] += dp[ i + 1 ];
                    if ( s[ i + 1 ] == '*' )
                    {
                        if ( s[ i ] == '1' )
                        {
                            dp[ i ] += dp[ i + 2 ] * 9;
                        }
                        if ( s[ i ] == '2' )
                        {
                            dp[ i ] += dp[ i + 2 ] * 6;
                        }
                    }
                    else if ( s[ i ] == '1' || ( s[ i ] == '2' && s[ i + 1 ] <= '6' ) )
                    {
                        dp[ i ] += dp[ i + 2 ];
                    }
                }

                static const uint64_t max_val = 1e9 + 7;
                if ( dp[ i ] > max_val )
                {
                    dp[ i ] = dp[ i ] % max_val;
                }
            }
        }

        return dp[ 0 ];
    }
};
}  // namespace dp_mine
}  // namespace

TEST( DecodeWaysII, dp_mine )
{
    dp_mine::Solution sn;
    EXPECT_EQ( 9, sn.numDecodings( "*" ) );
    EXPECT_EQ( 18, sn.numDecodings( "1*" ) );
    EXPECT_EQ( 96, sn.numDecodings( "**" ) );
    EXPECT_EQ( 291868912, sn.numDecodings( "*********" ) );
    EXPECT_EQ( 133236775, sn.numDecodings( "**********1111111111" ) );

    EXPECT_EQ( 11, sn.numDecodings( "*1" ) );
    EXPECT_EQ( 114, sn.numDecodings( "**1" ) );
    EXPECT_EQ( 999, sn.numDecodings( "***" ) );
    EXPECT_EQ( 58149, sn.numDecodings( "****1111" ) );
}

TEST( DecodeWaysII, dp_article )
{
    dp_article::Solution sn;
    EXPECT_EQ( 9, sn.numDecodings( "*" ) );
    EXPECT_EQ( 18, sn.numDecodings( "1*" ) );
    EXPECT_EQ( 96, sn.numDecodings( "**" ) );
    EXPECT_EQ( 291868912, sn.numDecodings( "*********" ) );
    EXPECT_EQ( 133236775, sn.numDecodings( "**********1111111111" ) );

    EXPECT_EQ( 11, sn.numDecodings( "*1" ) );
    EXPECT_EQ( 114, sn.numDecodings( "**1" ) );
    EXPECT_EQ( 999, sn.numDecodings( "***" ) );
    EXPECT_EQ( 58149, sn.numDecodings( "****1111" ) );
}