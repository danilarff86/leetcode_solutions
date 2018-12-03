#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    string
    longestPalindrome( string s )
    {
        if ( s.size( ) < 2 )
        {
            if ( s.size( ) > 1 )
            {
                return s[ 0 ] == s[ 1 ] ? s : s.substr( 0, 1 );
            }
            return s;
        }

        const auto str_len = s.size( );
        vector< vector< bool > > dp( str_len, vector< bool >( str_len ) );

        size_t longest_start = 0;
        size_t longest_len = 1;

        dp[ 0 ][ 0 ] = true;

        for ( size_t i = 1; i < str_len; ++i )
        {
            dp[ i ][ i ] = true;
            if ( s[ i ] == s[ i - 1 ] )
            {
                dp[ i - 1 ][ i ] = true;
                if ( longest_len < 2 )
                {
                    longest_start = i - 1;
                    longest_len = 2;
                }
            }
        }

        for ( size_t offset = 2; offset < str_len; ++offset )
        {
            for ( size_t start = 0; start < str_len - offset; ++start )
            {
                auto end = start + offset;
                if ( s[ start ] == s[ start + offset ] && dp[ start + 1 ][ end - 1 ] )
                {
                    dp[ start ][ end ] = true;
                    auto len = offset + 1;
                    if ( longest_len < len )
                    {
                        longest_len = len;
                        longest_start = start;
                    }
                }
            }
        }

        return s.substr( longest_start, longest_len );
    }
};
}  // namespace

TEST( LongestPalindromicSubstring, generic )
{
    Solution sn;
    EXPECT_EQ( "bab", sn.longestPalindrome( "babad" ) );
    EXPECT_EQ( "bb", sn.longestPalindrome( "cbbd" ) );
    EXPECT_EQ( "", sn.longestPalindrome( "" ) );
    EXPECT_EQ( "a", sn.longestPalindrome( "a" ) );
    EXPECT_EQ( "abcba", sn.longestPalindrome( "abcba" ) );
}