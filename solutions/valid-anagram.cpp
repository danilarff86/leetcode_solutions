#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isAnagram( string s, string t )
    {
        if ( s.size( ) != t.size( ) )
        {
            return false;
        }

        static const auto num_chars = 'z' - 'a' + 1;
        vector< int > sv( num_chars );
        vector< int > tv( num_chars );

        for ( size_t i = 0; i < s.size( ); i++ )
        {
            sv[ s[ i ] - 'a' ]++;
            tv[ t[ i ] - 'a' ]++;
        }

        return sv == tv;
    }
};
}  // namespace

TEST( ValidAnagram, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isAnagram( "anagram", "nagaram" ) );
    EXPECT_FALSE( sn.isAnagram( "rat", "car" ) );
}
