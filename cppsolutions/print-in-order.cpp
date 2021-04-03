#include "gtest/gtest.h"

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <thread>

using namespace std;

namespace
{
class Foo
{
public:
    Foo( )
        : print_second( false )
        , print_third( false )
    {
    }

    void
    first( function< void( ) > printFirst )
    {
        unique_lock< mutex > lk( m );
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst( );
        print_second = true;
        cv.notify_all( );
    }

    void
    second( function< void( ) > printSecond )
    {
        unique_lock< mutex > lk( m );
        cv.wait( lk, [this] { return print_second; } );
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond( );
        print_second = false;
        print_third = true;
        cv.notify_all( );
    }

    void
    third( function< void( ) > printThird )
    {
        unique_lock< mutex > lk( m );
        cv.wait( lk, [this] { return print_third; } );
        // printThird() outputs "third". Do not change or remove this line.
        printThird( );
    }

private:
    bool print_second;
    bool print_third;
    mutex m;
    condition_variable cv;
};
}  // namespace

TEST( PrintInOrder, generic )
{
    Foo sn;
    ostringstream oss;

    thread t3( [&sn, &oss]( ) { sn.third( [&oss]( ) { oss << "third"; } ); } );
    thread t2( [&sn, &oss]( ) { sn.second( [&oss]( ) { oss << "second"; } ); } );
    thread t1( [&sn, &oss]( ) { sn.first( [&oss]( ) { oss << "first"; } ); } );
    t1.join( );
    t2.join( );
    t3.join( );

    EXPECT_EQ( "firstsecondthird", oss.str( ) );
}
