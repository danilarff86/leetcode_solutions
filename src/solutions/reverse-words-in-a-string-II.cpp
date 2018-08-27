#include <algorithm>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    void
    reverseWords( string& s )
    {
        std::reverse( s.begin( ), s.end( ) );
        auto cit = s.begin( );
        while ( cit != s.end( ) )
        {
            const auto word_begin = isspace( *cit ) ? ++cit : cit++;
            while ( cit != s.end( ) && !isspace( *cit ) )
            {
                ++cit;
            }
            std::reverse( word_begin, cit );
        }
    }
};
}  // namespace

TEST( ReverseWordsInAStringII, generic )
{
    Solution sn;

    std::string s1 = "the sky is blue";
    sn.reverseWords( s1 );
    EXPECT_EQ( "blue is sky the", s1 );
}