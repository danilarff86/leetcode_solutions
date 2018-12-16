#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
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
        vector< string::value_type > s2;
        s2.reserve( s.size( ) );

        auto rcit = s.rbegin( );
        while ( rcit != s.rend( ) )
        {
            // Skip spaces
            while ( rcit != s.rend( ) && isspace( *rcit ) )
            {
                ++rcit;
            }
            auto word_end = rcit;

            // Find word start
            auto word_start = rcit;
            while ( rcit != s.rend( ) && !isspace( *rcit ) )
            {
                word_start = ++rcit;
            }

            if ( word_start != word_end )
            {
                // Copy word
                if ( !s2.empty( ) )
                {
                    s2.push_back( ' ' );
                }
                std::copy( word_start.base( ), word_end.base( ), back_inserter( s2 ) );
            }
        }

        s.assign( s2.begin( ), s2.end( ) );
    }
};
}  // namespace

TEST( ReverseWordsInAString, generic )
{
    Solution sn;

    std::string s1 = "the sky is blue";
    sn.reverseWords( s1 );
    EXPECT_EQ( "blue is sky the", s1 );

    std::string s2 = "  the sky is blue  ";
    sn.reverseWords( s2 );
    EXPECT_EQ( "blue is sky the", s2 );

    std::string s3 = " 1";
    sn.reverseWords( s3 );
    EXPECT_EQ( "1", s3 );

    std::string s4 = "hi!";
    sn.reverseWords( s4 );
    EXPECT_EQ( "hi!", s4 );
}