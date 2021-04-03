#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
namespace python
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
}  // namespace python

namespace mine
{
class Solution
{
public:
    int
    nthSuperUglyNumber( int n, const vector< int >& primes )
    {
        vector< int > super_ugly_numbers;
        priority_queue< uint64_t, vector< uint64_t >, greater< uint64_t > > heap;
        set< uint64_t > traversed;
        heap.push( 1 );

        while ( super_ugly_numbers.size( ) < n )
        {
            const auto num = heap.top( );
            super_ugly_numbers.push_back( num );
            heap.pop( );

            for ( const auto p : primes )
            {
                const auto new_prime = p * num;
                if ( traversed.find( new_prime ) == traversed.end( ) )
                {
                    heap.push( new_prime );
                    traversed.insert( new_prime );
                }
            }
        }

        return super_ugly_numbers.back( );
    }
};
}  // namespace mine
}  // namespace

TEST( SuperUglyNumber, generic )
{
    {
        python::Solution sn;
        EXPECT_EQ( 32, sn.nthSuperUglyNumber( 12, {2, 7, 13, 19} ) );
    }
    {
        mine::Solution sn;
        EXPECT_EQ( 32, sn.nthSuperUglyNumber( 12, {2, 7, 13, 19} ) );
    }
}
