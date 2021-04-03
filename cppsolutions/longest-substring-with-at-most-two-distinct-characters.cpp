#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    lengthOfLongestSubstringTwoDistinct( string s )
    {
        const int len = s.size( );

        int j = 0;
        int k = -1;
        int res = 0;

        for ( int i = 1; i < len; ++i )
        {
            if ( s[ i ] != s[ i - 1 ] )
            {
                if ( k >= 0 && s[ k ] != s[ i ] )
                {
                    res = max( i - j, res );
                    j = k + 1;
                }
                k = i - 1;
            }
        }
        return max( len - j, res );
    }
};
}  // namespace

TEST( LongestSubstringWithAtMostTwoDistinctCharacters, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.lengthOfLongestSubstringTwoDistinct( "eceba" ) );
    EXPECT_EQ( 7, sn.lengthOfLongestSubstringTwoDistinct( "ecceeecba" ) );
}