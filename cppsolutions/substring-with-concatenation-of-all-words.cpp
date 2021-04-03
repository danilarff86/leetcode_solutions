#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    findSubstring( string s, const vector< string >& words )
    {
        const auto word_sz = words.size( );
        if ( word_sz == 0 )
        {
            return {};
        }

        const auto word_length = words[ 0 ].length( );

        vector< int > word_counters;
        unordered_map< string, size_t > words_map;
        int index = 0;
        for ( const auto& word : words )
        {
            auto it = words_map.find( word );
            if ( it != words_map.end( ) )
            {
                ++word_counters[ it->second ];
            }
            else
            {
                words_map.insert( make_pair( word, index++ ) );
                word_counters.push_back( 1 );
            }
        }

        vector< int > res;
        vector< int > actual_word_counters( word_counters.size( ) );
        const auto substring_length = word_sz * word_length;

        if ( s.length( ) < substring_length )
        {
            return {};
        }

        for ( size_t i = 0; i <= s.length( ) - substring_length; i++ )
        {
            fill( actual_word_counters.begin( ), actual_word_counters.end( ), 0 );
            size_t words_matched = 0;
            for ( size_t i_word = i; i_word < i + substring_length; i_word += word_length )
            {
                const auto& word = s.substr( i_word, word_length );
                auto it = words_map.find( word );
                if ( it == words_map.end( ) )
                {
                    break;
                }
                auto& word_cnt = actual_word_counters[ it->second ];
                if ( word_cnt == word_counters[ it->second ] )
                {
                    break;
                }
                ++word_cnt;
                ++words_matched;
            }
            if ( words_matched == word_sz )
            {
                res.push_back( i );
            }
        }

        return res;
    }
};

vector< int >
sorted( vector< int >&& v )
{
    sort( v.begin( ), v.end( ) );
    return std::move( v );
}
}  // namespace

TEST( SubstringWithConcatenationOfAllWords, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< int >{0, 9} ),
               sorted( sn.findSubstring( "barfoothefoobarman", {"foo", "bar"} ) ) );
    EXPECT_EQ( ( vector< int >{} ),
               sorted( sn.findSubstring( "wordgoodgoodgoodbestword",
                                         {"word", "good", "best", "word"} ) ) );
    EXPECT_EQ( ( vector< int >{6, 9, 12} ),
               sorted( sn.findSubstring( "barfoofoobarthefoobarman", {"bar", "foo", "the"} ) ) );
    EXPECT_EQ( ( vector< int >{} ), sorted( sn.findSubstring( "", {"a"} ) ) );
    EXPECT_EQ( ( vector< int >{0, 1, 2} ),
               sorted( sn.findSubstring( "aaaaaaaa", {"aa", "aa", "aa"} ) ) );
}
