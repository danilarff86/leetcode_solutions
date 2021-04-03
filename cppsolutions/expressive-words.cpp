#include "gtest/gtest.h"

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    expressiveWords( const string& S, const vector< string >& words )
    {
        vector< uint8_t > group_len;
        vector< char > groups;
        for ( size_t i = 0; i < S.size( ); )
        {
            auto const group_char = S[ i ];
            auto cnt = 0;
            while ( i < S.size( ) && group_char == S[ i ] )
            {
                ++cnt;
                ++i;
            }
            groups.push_back( group_char );
            group_len.push_back( cnt );
        }

        int res = 0;

        for ( auto const& word : words )
        {
            size_t group_index = 0;
            for ( size_t i = 0; i < word.size( ); )
            {
                auto const group_char = word[ i ];
                if ( group_char != groups[ group_index ] )
                {
                    break;
                }

                auto cnt = 0;
                while ( i < word.size( ) && group_char == word[ i ] )
                {
                    ++cnt;
                    ++i;
                }

                if ( !( cnt == group_len[ group_index ]
                        || ( group_len[ group_index ] >= 3 && cnt < group_len[ group_index ] ) ) )
                {
                    break;
                }
                ++group_index;
            }
            if ( group_index == groups.size( ) )
            {
                ++res;
            }
        }

        return res;
    }
};
}  // namespace

TEST( ExpressiveWords, generic )
{
    Solution sn;
    EXPECT_EQ( 1, sn.expressiveWords( "heeellooo", {"hello", "hi", "helo"} ) );
}
