#include "gtest/gtest.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

namespace
{
vector< int >
sorted( vector< int > v )
{
    sort( v.begin( ), v.end( ) );
    return v;
}
}  // namespace

namespace fastest
{
class Solution
{
public:
    vector< int >
    powerfulIntegers( int x, int y, int bound )
    {
        unordered_set< int > integers;
        if ( y == 1 )
        {
            if ( x == 1 )
            {
                return bound >= 2 ? vector< int >{2} : vector< int >{};
            }

            for ( int x_pow = 1; x_pow < bound; x_pow *= x )
            {
                integers.insert( x_pow + 1 );
            }
        }
        else if ( x == 1 )
        {
            for ( int y_pow = 1; y_pow < bound; y_pow *= y )
            {
                integers.insert( y_pow + 1 );
            }
        }
        else
        {
            for ( int x_pow = 1; x_pow < bound; x_pow *= x )
            {
                for ( int y_pow = 1; ( x_pow + y_pow ) <= bound; y_pow *= y )
                {
                    integers.insert( x_pow + y_pow );
                }
            }
        }

        return vector< int >( integers.begin( ), integers.end( ) );
    }
};
}  // namespace fastest

namespace less_mem
{
class Solution
{
public:
    vector< int >
    powerfulIntegers( int x, int y, int bound )
    {
        vector< int > integers;
        if ( y == 1 )
        {
            if ( x == 1 )
            {
                return bound >= 2 ? vector< int >{2} : vector< int >{};
            }

            for ( int x_pow = 1; x_pow < bound; x_pow *= x )
            {
                integers.push_back( x_pow + 1 );
            }
        }
        else if ( x == 1 )
        {
            for ( int y_pow = 1; y_pow < bound; y_pow *= y )
            {
                integers.push_back( y_pow + 1 );
            }
        }
        else
        {
            for ( int x_pow = 1; x_pow < bound; x_pow *= x )
            {
                for ( int y_pow = 1; ( x_pow + y_pow ) <= bound; y_pow *= y )
                {
                    integers.push_back( x_pow + y_pow );
                }
            }
        }

        sort( integers.begin( ), integers.end( ) );
        integers.erase( unique( integers.begin( ), integers.end( ) ), integers.end( ) );
        return integers;
    }
};
}  // namespace less_mem

TEST( PowerfulIntegers, generic )
{
    {
        less_mem::Solution sn;
        EXPECT_EQ( ( vector< int >{2, 3, 4, 5, 7, 9, 10} ), sn.powerfulIntegers( 2, 3, 10 ) );
        EXPECT_EQ( ( vector< int >{2, 4, 6, 8, 10, 14} ), sn.powerfulIntegers( 3, 5, 15 ) );
        EXPECT_EQ( ( vector< int >{2, 3, 5, 9} ), sn.powerfulIntegers( 2, 1, 10 ) );
        EXPECT_EQ( ( vector< int >{2, 3, 5, 9, 17, 33, 65} ), sn.powerfulIntegers( 1, 2, 100 ) );
    }
    {
        fastest::Solution sn;
        EXPECT_EQ( ( vector< int >{2, 3, 4, 5, 7, 9, 10} ),
                   sorted( sn.powerfulIntegers( 2, 3, 10 ) ) );
        EXPECT_EQ( ( vector< int >{2, 4, 6, 8, 10, 14} ),
                   sorted( sn.powerfulIntegers( 3, 5, 15 ) ) );
        EXPECT_EQ( ( vector< int >{2, 3, 5, 9} ), sorted( sn.powerfulIntegers( 2, 1, 10 ) ) );
        EXPECT_EQ( ( vector< int >{2, 3, 5, 9, 17, 33, 65} ),
                   sorted( sn.powerfulIntegers( 1, 2, 100 ) ) );
    }
}
