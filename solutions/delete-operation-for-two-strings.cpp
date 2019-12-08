#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    minDistance( const string& word1, const string& word2 )
    {
        m_cache
            = vector< vector< int > >( word1.size( ) + 1, vector< int >( word2.size( ) + 1, -1 ) );
        return word1.size( ) + word2.size( )
               - 2 * lcs( word1, word2, word1.size( ), word2.size( ) );
    }

    int
    lcs( const string& s1, const string& s2, int l1, int l2 )
    {
        auto& cache_entry = m_cache[ l1 ][ l2 ];
        if ( cache_entry != -1 )
        {
            return cache_entry;
        }

        if ( l1 == 0 || l2 == 0 )
        {
            cache_entry = 0;
        }
        else if ( s1[ l1 - 1 ] == s2[ l2 - 1 ] )
        {
            cache_entry = 1 + lcs( s1, s2, l1 - 1, l2 - 1 );
        }
        else
        {
            cache_entry = max( lcs( s1, s2, l1 - 1, l2 ), lcs( s1, s2, l1, l2 - 1 ) );
        }

        return cache_entry;
    }

private:
    vector< vector< int > > m_cache;
};
}  // namespace

TEST( DeleteOperationForTwoStrings, generic )
{
    Solution sn;
    EXPECT_EQ( 2, sn.minDistance( "sea", "eat" ) );
}
