#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace old_variant
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
}  // namespace old_variant

namespace new_variant
{
class Solution
{
public:
    void
    reverseWords( string& s )
    {
        string res;
        res.reserve( s.length( ) );

        int j = s.length( );
        for ( int i = s.length( ) - 1; i >= 0; i-- )
        {
            if ( isspace( s[ i ] ) )
            {
                j = i;
            }
            else if ( i == 0 || isspace( s[ i - 1 ] ) )
            {
                if ( !res.empty( ) )
                {
                    res.push_back( ' ' );
                }
                res.append( s.substr( i, j - i ) );
            }
        }

        s = move( res );
    }
};
}  // namespace new_variant

TEST( ReverseWordsInAString, generic )
{
    {
        old_variant::Solution sn;

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

    {
        new_variant::Solution sn;

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
}