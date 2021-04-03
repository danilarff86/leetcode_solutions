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
    numDistinct( const string& s, const string& t )
    {
        vector< size_t > dp( t.size( ) + 1 );
        dp[ 0 ] = 1;
        for ( const auto c : s )
        {
            for ( size_t i = t.size( ); i > 0; i-- )
            {
                if ( c == t[ i - 1 ] )
                {
                    dp[ i ] += dp[ i - 1 ];
                }
            }
        }

        return dp.back( );
    }
};
}  // namespace

TEST( DistinctSubsequences, generic )
{
    Solution sn;
    EXPECT_EQ( 3, sn.numDistinct( "rabbbit", "rabbit" ) );
    EXPECT_EQ( 5, sn.numDistinct( "babgbag", "bag" ) );
    EXPECT_EQ(
        543744000,
        sn.numDistinct(
            "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylc"
            "wvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwft"
            "lxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfj"
            "afmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextf"
            "cozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqy"
            "kgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcg"
            "speynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjre"
            "qrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwet"
            "ioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhu"
            "nbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzd"
            "mzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelcziosk"
            "qtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo",
            "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys" ) );
}
