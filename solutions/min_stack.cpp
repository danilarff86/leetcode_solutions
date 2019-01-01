#include "gtest/gtest.h"

#include <algorithm>
#include <stack>

using namespace std;

namespace
{
class MinStack
{
public:
    /** initialize your data structure here. */
    MinStack( )
    {
    }

    void
    push( int x )
    {
        m_vals.push( x );
        m_mins.push( m_mins.empty( ) ? x : min( x, m_mins.top( ) ) );
    }

    void
    pop( )
    {
        m_vals.pop( );
        m_mins.pop( );
    }

    int
    top( )
    {
        return m_vals.top( );
    }

    int
    getMin( )
    {
        return m_mins.top( );
    }

private:
    stack< int > m_vals;
    stack< int > m_mins;
};
}  // namespace

TEST( MinStack, generic )
{
    {
        MinStack minStack;
        minStack.push( -2 );
        minStack.push( 0 );
        minStack.push( -3 );
        EXPECT_EQ( -3, minStack.getMin( ) );
        minStack.pop( );
        EXPECT_EQ( 0, minStack.top( ) );
        EXPECT_EQ( -2, minStack.getMin( ) );
    }
}
