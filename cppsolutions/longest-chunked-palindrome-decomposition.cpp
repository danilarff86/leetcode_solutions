#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace rolling_hash
{
class Solution
{
public:
    int
    longestDecomposition( const string& text )
    {
        int text_size = text.size( );
        int last_index = text_size / 2;

        int res = 1;

        static const int P_B = 27;
        static const int P_M = 1000005;

        vector< vector< int > > rolling_hash_dp( text.size( ), vector< int >( text.size( ) ) );
        for ( int i = 0; i < text.size( ); i++ )
        {
            int power = P_B;
            rolling_hash_dp[ i ][ i ] = ( text[ i ] - 'a' ) * power;
            for ( int j = i + 1; j < text.size( ); j++ )
            {
                power = ( power * P_B ) % P_M;
                rolling_hash_dp[ i ][ j ]
                    = ( rolling_hash_dp[ i ][ j - 1 ] + ( text[ j ] - 'a' ) * power ) % P_M;
            }
        }

        int offset = 0;
        for ( int i = 0; i < last_index; i++ )
        {
            if ( rolling_hash_dp[ offset ][ i ]
                 == rolling_hash_dp[ text_size - 1 - i ][ text_size - 1 - offset ] )
            {
                offset = i + 1;
                res += ( offset * 2 ) >= text_size ? 1 : 2;
            }
        }

        return res;
    }
};
}  // namespace rolling_hash

namespace string_compare
{
class Solution
{
public:
    int
    longestDecomposition( const string& text )
    {
        int text_size = text.size( );
        int last_index = text_size / 2;

        int res = 1;

        int offset = 0;
        for ( int i = 0; i < last_index; i++ )
        {
            if ( text.substr( offset, i - offset + 1 )
                 == text.substr( text_size - 1 - i, i - offset + 1 ) )
            {
                offset = i + 1;
                res += ( offset * 2 ) >= text_size ? 1 : 2;
            }
        }

        return res;
    }
};
}  // namespace string_compare
}  // namespace

TEST( LongestChunkedPalindromeDecomposition, generic )
{
    {
        rolling_hash::Solution sn;
        EXPECT_EQ( 7, sn.longestDecomposition( "ghiabcdefhelloadamhelloabcdefghi" ) );
        EXPECT_EQ( 1, sn.longestDecomposition( "merchant" ) );
        EXPECT_EQ( 11, sn.longestDecomposition( "antaprezatepzapreanta" ) );
        EXPECT_EQ( 3, sn.longestDecomposition( "aaa" ) );
        EXPECT_EQ( 2, sn.longestDecomposition( "azaz" ) );
        EXPECT_EQ( 4, sn.longestDecomposition( "rteazazrte" ) );
        EXPECT_EQ( 5, sn.longestDecomposition( "rteazgazrte" ) );
        // EXPECT_EQ(
        //     122,
        //     sn.longestDecomposition(
        //         "klzosgznatwxkhgbperdpvqpxtrujpvdxybmkrwwtdkwshjancajxmfehdklgjdrictlnienlbbwcmfebl"
        //         "epnikxkeibftbcdecssnakbmclgzudluhxzretmqslgtwqclmdrzecptxbmqqdlddullxqlvdajhcszerg"
        //         "xhiqpdglmkvkjjjppbaxjmihcgaxedqpwlououwlxedqpmihcgaxjpbajjpvkjglmkdhiqpzergxjhcsad"
        //         "llxqlvldduqqdtxbmdrzecpwqclmgtqsltmhxzreudlubmclgznakcsscdebtkeibfnikxblepfecmenlb"
        //         "bwirictlnjddklgehjxmfjancadkwshrwwtkdxybmpvtrujdpvqpxergbpwxkhznatglzosk" ) );
    }

    {
        string_compare::Solution sn;
        EXPECT_EQ( 7, sn.longestDecomposition( "ghiabcdefhelloadamhelloabcdefghi" ) );
        EXPECT_EQ( 1, sn.longestDecomposition( "merchant" ) );
        EXPECT_EQ( 11, sn.longestDecomposition( "antaprezatepzapreanta" ) );
        EXPECT_EQ( 3, sn.longestDecomposition( "aaa" ) );
        EXPECT_EQ( 2, sn.longestDecomposition( "azaz" ) );
        EXPECT_EQ( 4, sn.longestDecomposition( "rteazazrte" ) );
        EXPECT_EQ( 5, sn.longestDecomposition( "rteazgazrte" ) );
        // EXPECT_EQ(
        //     122,
        //     sn.longestDecomposition(
        //         "klzosgznatwxkhgbperdpvqpxtrujpvdxybmkrwwtdkwshjancajxmfehdklgjdrictlnienlbbwcmfebl"
        //         "epnikxkeibftbcdecssnakbmclgzudluhxzretmqslgtwqclmdrzecptxbmqqdlddullxqlvdajhcszerg"
        //         "xhiqpdglmkvkjjjppbaxjmihcgaxedqpwlououwlxedqpmihcgaxjpbajjpvkjglmkdhiqpzergxjhcsad"
        //         "llxqlvldduqqdtxbmdrzecpwqclmgtqsltmhxzreudlubmclgznakcsscdebtkeibfnikxblepfecmenlb"
        //         "bwirictlnjddklgehjxmfjancadkwshrwwtkdxybmpvtrujdpvqpxergbpwxkhznatglzosk" ) );
    }
}