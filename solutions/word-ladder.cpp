#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    int
    ladderLength( string beginWord, string endWord, vector< string >& wordList )
    {
        unordered_map< string, int > dict;
        for ( size_t i = 0; i < wordList.size( ); i++ )
        {
            dict.emplace( wordList[ i ], i );
        }
        auto end_word_it = dict.find( endWord );
        if ( end_word_it == dict.end( ) )
        {
            return {};
        }
        const auto end_word_index = end_word_it->second;
        wordList.push_back( beginWord );
        vector< int > current_level_words{int( wordList.size( ) - 1 )};
        vector< int > next_level_words;
        int level = 1;

        while ( !current_level_words.empty( ) )
        {
            vector< int > new_words;
            for ( auto const& i_word : current_level_words )
            {
                if ( i_word == end_word_index )
                {
                    return level;
                }

                string& word = wordList[ i_word ];
                for ( auto& c : word )
                {
                    char orig = c;
                    for ( c = 'a'; c <= 'z'; ++c )
                    {
                        auto dict_it = dict.find( word );
                        if ( dict_it != dict.end( ) )
                        {
                            new_words.push_back( dict_it->second );
                            next_level_words.push_back( dict_it->second );
                        }
                    }
                    c = orig;
                }
            }
            for ( const auto i_word : new_words )
            {
                dict.erase( wordList[ i_word ] );
            }
            current_level_words.swap( next_level_words );
            next_level_words.clear( );
            ++level;
        }

        return 0;
    }
};
}  // namespace

TEST( WordLadder, generic )
{
    Solution sn;
    vector< string > word_list{"hot", "dot", "dog", "lot", "log", "cog"};
    EXPECT_EQ( 5, sn.ladderLength( "hit", "cog", word_list ) );

    word_list = {"hot", "dot", "dog", "lot", "log"};
    EXPECT_EQ( 0, sn.ladderLength( "hit", "cog", word_list ) );

    word_list = {"a", "b", "c"};
    EXPECT_EQ( 2, sn.ladderLength( "a", "c", word_list ) );
}
