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
        if ( m_mins.empty( ) || x <= m_mins.top( ) )
        {
            m_mins.push( x );
        }
    }

    void
    pop( )
    {
        if ( m_vals.top( ) == m_mins.top( ) )
        {
            m_mins.pop( );
        }
        m_vals.pop( );
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
