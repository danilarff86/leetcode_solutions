#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace
{
namespace insertion
{
class MedianFinder
{
public:
    void
    addNum( int num )
    {
        data.insert( lower_bound( data.begin( ), data.end( ), num ), num );
    }

    double
    findMedian( )
    {
        const auto half = data.size( ) / 2;
        return data.size( ) & 1 ? data[ half ] : double( data[ half ] + data[ half - 1 ] ) / 2.;
    }

private:
    vector< int > data;
};
}  // namespace insertion

namespace heap
{
class MedianFinder
{
public:
    void
    addNum( int num )
    {
        if ( high.empty( ) )
        {
            high.push( num );
            return;
        }

        if ( num < high.top( ) )
        {
            low.push( num );
            if ( low.size( ) > high.size( ) )
            {
                high.push( low.top( ) );
                low.pop( );
            }
        }
        else
        {
            high.push( num );
            if ( high.size( ) - low.size( ) > 1 )
            {
                low.push( high.top( ) );
                high.pop( );
            }
        }
    }

    double
    findMedian( )
    {
        return high.size( ) > low.size( ) ? double( high.top( ) )
                                          : double( high.top( ) + low.top( ) ) / 2.;
    }

private:
    priority_queue< int > low;
    priority_queue< int, std::vector< int >, greater< int > > high;
};
}  // namespace heap
}  // namespace

TEST( FindMedianfromDataStream, generic )
{
    {
        insertion::MedianFinder sn;
        sn.addNum( 1 );
        sn.addNum( 2 );
        EXPECT_DOUBLE_EQ( 1.5, sn.findMedian( ) );
        sn.addNum( 3 );
        EXPECT_DOUBLE_EQ( 2., sn.findMedian( ) );
    }
    {
        insertion::MedianFinder sn;
        sn.addNum( -1 );
        EXPECT_DOUBLE_EQ( -1, sn.findMedian( ) );
        sn.addNum( -2 );
        EXPECT_DOUBLE_EQ( -1.5, sn.findMedian( ) );
        sn.addNum( -3 );
        EXPECT_DOUBLE_EQ( -2, sn.findMedian( ) );
        sn.addNum( -4 );
        EXPECT_DOUBLE_EQ( -2.5, sn.findMedian( ) );
        sn.addNum( -5 );
        EXPECT_DOUBLE_EQ( -3, sn.findMedian( ) );
    }

    {
        heap::MedianFinder sn;
        sn.addNum( 1 );
        sn.addNum( 2 );
        EXPECT_DOUBLE_EQ( 1.5, sn.findMedian( ) );
        sn.addNum( 3 );
        EXPECT_DOUBLE_EQ( 2., sn.findMedian( ) );
    }
    {
        heap::MedianFinder sn;
        sn.addNum( -1 );
        EXPECT_DOUBLE_EQ( -1, sn.findMedian( ) );
        sn.addNum( -2 );
        EXPECT_DOUBLE_EQ( -1.5, sn.findMedian( ) );
        sn.addNum( -3 );
        EXPECT_DOUBLE_EQ( -2, sn.findMedian( ) );
        sn.addNum( -4 );
        EXPECT_DOUBLE_EQ( -2.5, sn.findMedian( ) );
        sn.addNum( -5 );
        EXPECT_DOUBLE_EQ( -3, sn.findMedian( ) );
    }
}
