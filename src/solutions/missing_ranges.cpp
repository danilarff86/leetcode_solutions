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
    findMissingRanges( vector< int > vals, int start, int end )
    {
        vector< string > res;
        for ( auto v : vals )
        {
            if ( v > end )
            {
                break;
            }
            if ( v - start > 0 )
            {
                res.emplace_back( getRange( start, v - 1 ) );
            }
            start = v >= start ? v + 1 : start;
        }
        if ( end - start > 1 )
        {
            res.emplace_back( getRange( start, end ) );
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
    EXPECT_TRUE( ( vector< string >{"2", "4->49", "51->74", "76->99"}
                   == sn.findMissingRanges( vector< int >{0, 1, 3, 50, 75}, 0, 99 ) ) );
    EXPECT_TRUE(
        ( vector< string >{} == sn.findMissingRanges( vector< int >{0, 1, 2, 3, 4}, 0, 4 ) ) );
    EXPECT_TRUE( ( vector< string >{"0->99"} == sn.findMissingRanges( vector< int >{}, 0, 99 ) ) );
    EXPECT_TRUE( ( vector< string >{"0->1", "4->49", "51->74", "76->99"}
                   == sn.findMissingRanges( vector< int >{2, 3, 50, 75}, 0, 99 ) ) );
    EXPECT_TRUE( ( vector< string >{"0", "4->49", "51->74", "76->99"}
                   == sn.findMissingRanges( vector< int >{1, 2, 3, 50, 75}, 0, 99 ) ) );
    EXPECT_TRUE( ( vector< string >{"0", "4->49", "51->74", "76->99"}
                   == sn.findMissingRanges( vector< int >{1, 2, 3, 50, 75, 101}, 0, 99 ) ) );
    EXPECT_TRUE( ( vector< string >{"34->49", "51->74", "76->99"}
                   == sn.findMissingRanges( vector< int >{1, 2, 3, 50, 75}, 34, 99 ) ) );
}