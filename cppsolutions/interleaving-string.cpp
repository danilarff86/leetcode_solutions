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
    isInterleave( const string& s1, const string& s2, const string& s3 )
    {
        const auto ROWS = s1.size( );
        const auto COLS = s2.size( );
        if ( ROWS + COLS != s3.size( ) )
        {
            return false;
        }
        vector< vector< bool > > dp( ROWS + 1, vector< bool >( COLS + 1 ) );
        dp[ 0 ][ 0 ] = true;

        for ( size_t i = 1; i <= ROWS; i++ )
        {
            dp[ i ][ 0 ] = s3[ i - 1 ] == s1[ i - 1 ] && dp[ i - 1 ][ 0 ];
        }
        for ( size_t i = 1; i <= COLS; i++ )
        {
            dp[ 0 ][ i ] = s3[ i - 1 ] == s2[ i - 1 ] && dp[ 0 ][ i - 1 ];
        }

        for ( size_t i = 1; i <= ROWS; i++ )
        {
            for ( size_t j = 1; j <= COLS; j++ )
            {
                const auto c = s3[ i + j - 1 ];
                if ( c == s1[ i - 1 ] && dp[ i - 1 ][ j ] )
                {
                    dp[ i ][ j ] = true;
                }
                if ( c == s2[ j - 1 ] && dp[ i ][ j - 1 ] )
                {
                    dp[ i ][ j ] = true;
                }
            }
        }

        return dp[ ROWS ][ COLS ];
    }
};
}  // namespace

TEST( InterleavingString, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isInterleave( "aabcc", "dbbca", "aadbbcbcac" ) );
    EXPECT_FALSE( sn.isInterleave( "aabcc", "dbbca", "aadbbbaccc" ) );
}
