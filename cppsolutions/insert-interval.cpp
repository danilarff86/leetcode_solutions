#include <algorithm>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< vector< int > >
    insert( vector< vector< int > >& intervals, vector< int >& newInterval )
    {
        auto it1 = lower_bound( intervals.begin( ), intervals.end( ), newInterval,
                                []( const vector< int >& lhs, const vector< int >& rhs ) {
                                    return lhs[ 1 ] < rhs[ 0 ];
                                } );

        auto it2 = lower_bound( intervals.begin( ), intervals.end( ), newInterval,
                                []( const vector< int >& lhs, const vector< int >& rhs ) {
                                    return lhs[ 1 ] < rhs[ 1 ];
                                } );

        if ( it1 != intervals.end( ) )
        {
            if ( ( *it1 )[ 0 ] < newInterval[ 0 ] )
            {
                newInterval[ 0 ] = ( *it1 )[ 0 ];
            }
            if ( ( *it1 )[ 1 ] > newInterval[ 1 ] && ( *it1 )[ 0 ] <= newInterval[ 1 ] )
            {
                newInterval[ 1 ] = ( *it1 )[ 1 ];
            }
        }

        if ( it2 != intervals.end( ) )
        {
            if ( ( *it2 )[ 0 ] <= newInterval[ 1 ] )
            {
                newInterval[ 1 ] = ( *it2 )[ 1 ];
                it2 = next( it2 );
            }
        }

        auto it_new = intervals.erase( it1, it2 );
        intervals.insert( it_new, newInterval );
        return intervals;
    }
};
}  // namespace

TEST( InsertInterval, generic )
{
    Solution sn;

    vector< vector< int > > intervals;
    vector< int > newInterval;

    intervals = {{1, 3}, {6, 9}};
    newInterval = {2, 5};
    EXPECT_EQ( ( vector< vector< int > >{{1, 5}, {6, 9}} ), sn.insert( intervals, newInterval ) );

    intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    newInterval = {4, 8};
    EXPECT_EQ( ( vector< vector< int > >{{1, 2}, {3, 10}, {12, 16}} ),
               sn.insert( intervals, newInterval ) );

    intervals = {{5, 7}, {9, 11}};
    newInterval = {1, 3};
    EXPECT_EQ( ( vector< vector< int > >{{1, 3}, {5, 7}, {9, 11}} ),
               sn.insert( intervals, newInterval ) );

    intervals = {{5, 7}, {9, 11}};
    newInterval = {15, 17};
    EXPECT_EQ( ( vector< vector< int > >{{5, 7}, {9, 11}, {15, 17}} ),
               sn.insert( intervals, newInterval ) );

    intervals = {};
    newInterval = {5, 7};
    EXPECT_EQ( ( vector< vector< int > >{{5, 7}} ), sn.insert( intervals, newInterval ) );

    intervals = {{1, 5}};
    newInterval = {2, 7};
    EXPECT_EQ( ( vector< vector< int > >{{1, 7}} ), sn.insert( intervals, newInterval ) );

    intervals = {{0, 2}, {3, 3}, {6, 11}};
    newInterval = {9, 15};
    EXPECT_EQ( ( vector< vector< int > >{{0, 2}, {3, 3}, {6, 15}} ),
               sn.insert( intervals, newInterval ) );

    intervals = {{1, 5}};
    newInterval = {2, 3};
    EXPECT_EQ( ( vector< vector< int > >{{1, 5}} ), sn.insert( intervals, newInterval ) );

    intervals = {{1, 5}};
    newInterval = {0, 3};
    EXPECT_EQ( ( vector< vector< int > >{{0, 5}} ), sn.insert( intervals, newInterval ) );

    intervals = {{1, 5}, {6, 8}};
    newInterval = {3, 7};
    EXPECT_EQ( ( vector< vector< int > >{{1, 8}} ), sn.insert( intervals, newInterval ) );
}
