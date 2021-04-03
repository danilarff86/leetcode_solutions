#include <algorithm>
#include <set>
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
    vector< string >
    watchedVideosByFriends( const vector< vector< string > >& watchedVideos,
                            const vector< vector< int > >& friends,
                            int id,
                            int level )
    {
        set< int > s[ 2 ];
        auto current_level_friends = &s[ 0 ];
        auto next_level_friends = &s[ 1 ];
        set< int > visited_friends;
        current_level_friends->insert( id );
        visited_friends.insert( id );
        for ( auto current_level = 0; current_level < level; ++current_level )
        {
            for ( auto level_friend : *current_level_friends )
            {
                for ( auto f : friends[ level_friend ] )
                {
                    if ( visited_friends.find( f ) == visited_friends.end( ) )
                    {
                        next_level_friends->insert( f );
                        visited_friends.insert( f );
                    }
                }
            }
            current_level_friends->clear( );
            swap( current_level_friends, next_level_friends );
        }

        unordered_map< string, int > watchedVideosMap;
        for ( auto level_friend : *current_level_friends )
        {
            for ( auto const& video : watchedVideos[ level_friend ] )
            {
                watchedVideosMap[ video ] += 1;
            }
        }
        vector< string > res;
        res.reserve( watchedVideos.size( ) );
        for ( auto const& video : watchedVideosMap )
        {
            res.push_back( video.first );
        }

        std::sort( res.begin( ), res.end( ),
                   [&watchedVideosMap]( const string& lhs, const string& rhs ) -> bool {
                       auto const lhs_cnt = watchedVideosMap[ lhs ];
                       auto const rhs_cnt = watchedVideosMap[ rhs ];
                       return lhs_cnt < rhs_cnt || ( ( lhs_cnt == rhs_cnt ) && ( lhs < rhs ) );
                   } );

        return res;
    }
};
}  // namespace

TEST( GetWatchedVideosByYourFriends, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< string >{"B", "C"} ),
               sn.watchedVideosByFriends( {{"A", "B"}, {"C"}, {"B", "C"}, {"D"}},
                                          {{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 1 ) );
    EXPECT_EQ( ( vector< string >( {"D"} ) ),
               sn.watchedVideosByFriends( {{"A", "B"}, {"C"}, {"B", "C"}, {"D"}},
                                          {{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 2 ) );
}
