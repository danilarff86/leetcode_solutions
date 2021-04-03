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
    vector< vector< string > >
    findLadders( string beginWord, string endWord, vector< string >& wordList )
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
        using Path = vector< int >;
        vector< Path > current_level_path;
        vector< Path > next_level_path{Path{int( wordList.size( ) - 1 )}};

        while ( !next_level_path.empty( ) )
        {
            current_level_path.swap( next_level_path );
            next_level_path.clear( );
            vector< int > new_words;
            for ( auto const& path : current_level_path )
            {
                if ( path.back( ) == end_word_index )
                {
                    return prepare_result( current_level_path, wordList, end_word_index );
                }

                string& word = wordList[ path.back( ) ];
                for ( auto& c : word )
                {
                    char orig = c;
                    for ( c = 'a'; c <= 'z'; ++c )
                    {
                        auto dict_it = dict.find( word );
                        if ( dict_it != dict.end( ) )
                        {
                            Path new_path = path;
                            new_path.push_back( dict_it->second );
                            new_words.push_back( dict_it->second );
                            next_level_path.push_back( new_path );
                        }
                    }
                    c = orig;
                }
            }
            for ( const auto i_word : new_words )
            {
                dict.erase( wordList[ i_word ] );
            }
        }

        return {};
    }

private:
    vector< vector< string > >
    prepare_result( vector< vector< int > >& path_list,
                    vector< string >& word_list,
                    int end_word_index )
    {
        vector< vector< string > > res;
        res.reserve( path_list.size( ) );
        for ( const auto& path : path_list )
        {
            if ( path.back( ) == end_word_index )
            {
                vector< string > string_seq;
                string_seq.reserve( path.size( ) );
                for ( auto i_word : path )
                {
                    string_seq.push_back( word_list[ i_word ] );
                }
                res.push_back( string_seq );
            }
        }

        return res;
    }
};
}  // namespace

TEST( WordLadderII, generic )
{
    Solution sn;
    vector< string > word_list{"hot", "dot", "dog", "lot", "log", "cog"};
    EXPECT_EQ( ( vector< vector< string > >{{"hit", "hot", "dot", "dog", "cog"},
                                            {"hit", "hot", "lot", "log", "cog"}} ),
               sn.findLadders( "hit", "cog", word_list ) );

    word_list = {"hot", "dot", "dog", "lot", "log"};
    EXPECT_EQ( ( vector< vector< string > >{} ), sn.findLadders( "hit", "cog", word_list ) );

    word_list = {"a", "b", "c"};
    EXPECT_EQ( ( vector< vector< string > >{{"a", "c"}} ), sn.findLadders( "a", "c", word_list ) );
}
