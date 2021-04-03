#include <queue>
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
    topKFrequent( const vector< int >& nums, int k )
    {
        unordered_map< int, int > occurences;
        for ( auto n : nums )
        {
            occurences[ n ] += 1;
        }

        priority_queue< pair< int, int > > heap;
        for ( auto& record : occurences )
        {
            heap.push( {record.second, record.first} );
        }

        vector< int > res;
        while ( res.size( ) < k )
        {
            res.push_back( heap.top( ).second );
            heap.pop( );
        }

        return res;
    }
};
}  // namespace

TEST( TopKFrequentElements, generic )
{
    {
        Solution sn;
        EXPECT_EQ( ( vector< int >{1, 2} ), sn.topKFrequent( {1, 1, 1, 2, 2, 3}, 2 ) );
    }
}
