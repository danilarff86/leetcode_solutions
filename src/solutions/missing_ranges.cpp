#include <limits>
#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< string >
    findMissingRanges( const vector< int >& nums, int lower, int upper )
    {
        vector< string > res;
        for ( auto v : nums )
        {
            if ( v > lower )
            {
                res.emplace_back( getRange( lower, v - 1 ) );
            }
            if ( v == upper )
            {
                return res;
            }
            lower = v + 1;
        }
        if ( upper >= lower )
        {
            res.emplace_back( getRange( lower, upper ) );
        }
        return res;
    }

private:
    string
    getRange( int from, int to )
    {
        return ( from == to ) ? std::to_string( from )
                              : std::to_string( from ) + "->" + std::to_string( to );
    }
};
}  // namespace

TEST( MissingRanges, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< string >{"2", "4->49", "51->74", "76->99"} ),
               sn.findMissingRanges( vector< int >{0, 1, 3, 50, 75}, 0, 99 ) );
    EXPECT_EQ( ( vector< string >{} ), sn.findMissingRanges( vector< int >{0, 1, 2, 3, 4}, 0, 4 ) );
    EXPECT_EQ( ( vector< string >{"0->99"} ), sn.findMissingRanges( vector< int >{}, 0, 99 ) );
    EXPECT_EQ( ( vector< string >{"0->1", "4->49", "51->74", "76->99"} ),
               sn.findMissingRanges( vector< int >{2, 3, 50, 75}, 0, 99 ) );
    EXPECT_EQ( ( vector< string >{"0", "4->49", "51->74", "76->99"} ),
               sn.findMissingRanges( vector< int >{1, 2, 3, 50, 75}, 0, 99 ) );
    EXPECT_EQ( ( vector< string >{"0", "4->49", "51->74", "76->99"} ),
               sn.findMissingRanges( vector< int >{1, 2, 3, 50, 75}, 0, 99 ) );
    EXPECT_EQ( ( vector< string >{"34->49", "51->74", "76->99"} ),
               sn.findMissingRanges( vector< int >{50, 75}, 34, 99 ) );
    EXPECT_EQ( ( vector< string >{"1"} ), sn.findMissingRanges( vector< int >{}, 1, 1 ) );
    EXPECT_EQ( ( vector< string >{"0->6", "8->9"} ),
               sn.findMissingRanges( vector< int >{7}, 0, 9 ) );
    EXPECT_EQ( ( vector< string >{"0->2147483646"} ),
               sn.findMissingRanges( vector< int >{2147483647}, 0, 2147483647 ) );
    EXPECT_EQ( ( vector< string >{"-2147483647->2147483646"} ),
               sn.findMissingRanges( vector< int >{int( -2147483648 ), int( 2147483647 )},
                                     int( -2147483648 ), int( 2147483647 ) ) );
    EXPECT_EQ( ( vector< string >{"-2147483647->-1", "1->2147483646"} ),
               sn.findMissingRanges( vector< int >{int( -2147483648 ), int( -2147483648 ), 0,
                                                   int( 2147483647 ), int( 2147483647 )},
                                     int( -2147483648 ), int( 2147483647 ) ) );
}