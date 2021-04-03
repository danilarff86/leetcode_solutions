#include "gtest/gtest.h"

#include <string>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    string
    minWindow( const string& s, const string& t )
    {
        const auto S_LEN = s.size( );
        const auto T_LEN = t.size( );
        int s_table[ 0xFF ]{};
        int t_table[ 0xFF ]{};
        for ( const auto c : t )
        {
            ++t_table[ c ];
        }
        int match_cnt = 0;

        int best_offset = 0;
        int best_len = S_LEN + 1;

        int begin = 0;
        int end = 0;
        while ( end < S_LEN )
        {
            while ( end < S_LEN && match_cnt < T_LEN )
            {
                const auto c = s[ end++ ];
                if ( ++s_table[ c ] <= t_table[ c ] )
                {
                    ++match_cnt;
                }
            }

            while ( match_cnt == T_LEN )
            {
                const auto c = s[ begin++ ];
                if ( --s_table[ c ] < t_table[ c ] )
                {
                    --match_cnt;
                }
            }

            const auto len = end - begin + 1;
            if ( len < best_len )
            {
                best_offset = begin - 1;
                best_len = len;
            }
        }

        return best_len <= S_LEN ? s.substr( best_offset, best_len ) : "";
    }
};
}  // namespace

TEST( MinimumWindowSubstring, generic )
{
    Solution sn;
    EXPECT_EQ( "BANC", sn.minWindow( "ADOBECODEBANC", "ABC" ) );
}
