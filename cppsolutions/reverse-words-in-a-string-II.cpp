#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace old_variant
{
class Solution
{
public:
    void
    reverseWords( vector< char >& str )
    {
        std::reverse( str.begin( ), str.end( ) );
        auto cit = str.begin( );
        while ( cit != str.end( ) )
        {
            const auto word_begin = isspace( *cit ) ? ++cit : cit++;
            while ( cit != str.end( ) && !isspace( *cit ) )
            {
                ++cit;
            }
            std::reverse( word_begin, cit );
        }
    }
};
}  // namespace old_variant

namespace new_variant
{
class Solution
{
public:
    void
    reverseWords( vector< char >& str )
    {
        std::reverse( str.begin( ), str.end( ) );
        auto cit = str.begin( );
        while ( cit != str.end( ) )
        {
            const auto word_begin = cit;
            while ( cit != str.end( ) && !isspace( *cit ) )
            {
                ++cit;
            }
            std::reverse( word_begin, cit );
            if ( cit != str.end( ) && isspace( *cit ) )
            {
                ++cit;
            }
        }
    }
};
}  // namespace new_variant

TEST( ReverseWordsInAStringII, generic )
{
    {
        old_variant::Solution sn;

        string s1 = "the sky is blue";
        vector< char > v1( s1.begin( ), s1.end( ) );
        sn.reverseWords( v1 );
        EXPECT_EQ( "blue is sky the", string( v1.data( ), v1.size( ) ) );
    }

    {
        new_variant::Solution sn;

        string s1 = "the sky is blue";
        vector< char > v1( s1.begin( ), s1.end( ) );
        sn.reverseWords( v1 );
        EXPECT_EQ( "blue is sky the", string( v1.data( ), v1.size( ) ) );
    }
}