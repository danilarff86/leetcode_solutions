#include <algorithm>
#include <climits>
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
    minDistance( const string& word1, const string& word2 )
    {
        vector< vector< int > > dp( word1.size( ) + 1, vector< int >( word2.size( ) + 1 ) );

        for ( int i = 1; i < word1.size( ) + 1; i++ )
        {
            dp[ i ][ 0 ] = i;
        }
        for ( int i = 1; i < word2.size( ) + 1; i++ )
        {
            dp[ 0 ][ i ] = i;
        }

        for ( int w1 = 1; w1 <= word1.size( ); w1++ )
        {
            for ( int w2 = 1; w2 <= word2.size( ); w2++ )
            {
                const int current_char_cost = word1[ w1 - 1 ] != word2[ w2 - 1 ];
                const auto continue_cost = dp[ w1 - 1 ][ w2 - 1 ] + current_char_cost;
                const auto remove_or_insert_cost
                    = min( dp[ w1 ][ w2 - 1 ], dp[ w1 - 1 ][ w2 ] ) + 1;
                dp[ w1 ][ w2 ] = min( continue_cost, remove_or_insert_cost );
            }
        }

        return dp[ word1.size( ) ][ word2.size( ) ];
    }
};
}  // namespace

TEST( EditDistance, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.minDistance( "horse", "ros" ) );
    EXPECT_EQ( 5, sn.minDistance( "intention", "execution" ) );
}
