#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    lengthOfLongestSubstring( string s )
    {
        vector< int > occurences( sizeof( char ) * 0xff, -1 );
        const int last = s.size( );
        int start = 0;
        int res = 0;
        for ( int i = 0; i < last; ++i )
        {
            auto& last_occurence = occurences[ s[ i ] ];
            if ( last_occurence >= start )
            {
                res = max( res, i - start );
                start = last_occurence + 1;
            }
            last_occurence = i;
        }

        return max( res, last - start );
    }
};
}  // namespace

TEST( LongestSubstringWithoutRepeatingCharacters, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.lengthOfLongestSubstring( "abcabcbb" ) );
    EXPECT_EQ( 1, sn.lengthOfLongestSubstring( "bbbbb" ) );
    EXPECT_EQ( 3, sn.lengthOfLongestSubstring( "pwwkew" ) );
    EXPECT_EQ( 5, sn.lengthOfLongestSubstring( "abcde" ) );
}