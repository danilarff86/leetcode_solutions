#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace
{
namespace recurse_with_memoization
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
}  // namespace recurse_with_memoization

namespace dp
{
class Solution
{
public:
    int
    minDistance( const string& word1, const string& word2 )
    {
        vector< vector< int > > dp( word1.size( ) + 1, vector< int >( word2.size( ) + 1 ) );
        for ( size_t i = 0; i <= word1.size( ); i++ )
        {
            for ( size_t j = 0; j <= word2.size( ); j++ )
            {
                if ( i == 0 || j == 0 )
                {
                    continue;
                }
                if ( word1[ i - 1 ] == word2[ j - 1 ] )
                {
                    dp[ i ][ j ] = 1 + dp[ i - 1 ][ j - 1 ];
                }
                else
                {
                    dp[ i ][ j ] = max( dp[ i - 1 ][ j ], dp[ i ][ j - 1 ] );
                }
            }
        }
        return word1.size( ) + word2.size( ) - 2 * dp[ word1.size( ) ][ word2.size( ) ];
    }
};
}  // namespace dp
}  // namespace

TEST( DeleteOperationForTwoStrings, generic )
{
    dp::Solution sn;
    EXPECT_EQ( 2, sn.minDistance( "sea", "eat" ) );
}
