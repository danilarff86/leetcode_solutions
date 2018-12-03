#include <cstdlib>
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
    longestPalindrome_basic( string s )
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

    string
    longestPalindrome( string s )
    {
        int start = 0;
        int count = 0;

        for ( int i = 0; i < s.size( ); ++i )
        {
            const auto len1 = expand_around_center( s, i, i );
            const auto len2 = expand_around_center( s, i, i + 1 );
            const auto len = max( len1, len2 );
            if ( len > count )
            {
                count = len;
                start = i - ( ( len - 1 ) / 2 );
            }
        }

        return s.substr( start, count );
    }

private:
    inline int
    expand_around_center( const string& s, int start, int end )
    {
        while ( start >= 0 && end < s.size( ) && s[ start ] == s[ end ] )
        {
            --start;
            ++end;
        }

        return end - start - 1;
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