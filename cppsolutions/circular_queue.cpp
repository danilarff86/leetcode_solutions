#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class MyQueue
{
public:
    explicit MyQueue( int capacity = 10 )
        : m_data( capacity )
        , m_wr( 0 )
        , m_rd( 0 )
        , m_size( 0 )
    {
    }

    bool
    push( int v )
    {
        if ( m_size == m_data.size( ) )
        {
            return false;
        }

        m_data[ m_wr++ ] = v;
        ++m_size;
        if ( m_wr >= m_data.size( ) )
        {
            m_wr = 0;
        }

        return true;
    }

    int
    top( )
    {
        if ( empty( ) )
        {
            throw std::runtime_error( "queue is empty" );
        }

        return m_data[ m_rd ];
    }

    void
    pop( )
    {
        if ( empty( ) )
        {
            throw std::runtime_error( "queue is empty" );
        }

        ++m_rd;
        --m_size;
        if ( m_rd >= m_data.size( ) )
        {
            m_rd = 0;
        }
    }

    int
    size( ) const
    {
        return m_size;
    }

    bool
    empty( ) const
    {
        return m_size == 0;
    }

private:
    vector< int > m_data;
    int m_rd;
    int m_wr;
    int m_size;
};

TEST( MyQueue, generic )
{
    MyQueue mq( 2 );
    EXPECT_TRUE( mq.empty( ) );
    mq.push( 10 );
    EXPECT_EQ( 1, mq.size( ) );
    mq.push( 20 );
    EXPECT_EQ( 2, mq.size( ) );
    EXPECT_FALSE( mq.push( 30 ) );
    EXPECT_EQ( 2, mq.size( ) );
    EXPECT_EQ( 10, mq.top( ) );
    mq.pop( );
    EXPECT_EQ( 1, mq.size( ) );
    EXPECT_TRUE( mq.push( 30 ) );
    EXPECT_EQ( 2, mq.size( ) );
    EXPECT_EQ( 20, mq.top( ) );
    mq.pop( );
    EXPECT_EQ( 1, mq.size( ) );
    EXPECT_EQ( 30, mq.top( ) );
    mq.pop( );
    EXPECT_TRUE( mq.empty( ) );
}