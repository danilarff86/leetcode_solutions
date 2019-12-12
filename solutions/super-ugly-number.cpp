#include "gtest/gtest.h"

#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    nthSuperUglyNumber( int n, const vector< int >& primes )
    {
        vector< int > super_ugly_numbers;
        priority_queue< int, vector< int >, greater< int > > heap;
        heap.push( 1 );
        unordered_map< int, vector< pair< int, int > > > indices;
        vector< pair< int, int > > tmp;
        for ( auto p : primes )
        {
            tmp.push_back( make_pair( 0, p ) );
        }
        indices[ 1 ] = move( tmp );

        while ( super_ugly_numbers.size( ) < n )
        {
            super_ugly_numbers.push_back( heap.top( ) );
            heap.pop( );
            for ( const auto& tup : indices[ super_ugly_numbers.back( ) ] )
            {
                const auto new_ugly = super_ugly_numbers[ tup.first ] * tup.second;
                if ( indices.find( new_ugly ) != indices.end( ) )
                {
                    indices[ new_ugly ].push_back( {tup.first + 1, tup.second} );
                }
                else
                {
                    indices[ new_ugly ] = {{tup.first + 1, tup.second}};
                    heap.push( new_ugly );
                }
            }
            indices.erase( super_ugly_numbers.back( ) );
        }

        return super_ugly_numbers.back( );
    }
};
}  // namespace

TEST( SuperUglyNumber, generic )
{
    Solution sn;
    EXPECT_EQ( 32, sn.nthSuperUglyNumber( 12, {2, 7, 13, 19} ) );
}
