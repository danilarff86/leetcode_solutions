#include "heap.h"
#include "gtest/gtest.h"

using namespace std;

TEST( HeapImpl, generic )
{
    {
        heap::Heap< int > instance;
        instance.push( 100 );
        EXPECT_EQ( 100, instance.top( ) );
        instance.push( 10 );
        EXPECT_EQ( 10, instance.top( ) );
        instance.pop( );
        EXPECT_EQ( 100, instance.top( ) );
    }

    {
        heap::Heap< int, std::vector< int >, std::greater< int > > instance;
        instance.push( 10 );
        EXPECT_EQ( 10, instance.top( ) );
        instance.push( 100 );
        EXPECT_EQ( 100, instance.top( ) );
        instance.pop( );
        EXPECT_EQ( 10, instance.top( ) );
    }
}