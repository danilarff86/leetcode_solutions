#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace heap
{
template < typename T,
           typename Container = std::vector< T >,
           typename Compare = std::less< typename Container::value_type > >
class Heap
{
public:
    using IndexType = typename Container::size_type;

public:
    Heap( )
        : m_comparator( )
    {
    }

public:
    const T&
    top( ) const
    {
        if ( m_items.empty( ) )
        {
            throw std::runtime_error( "heap is empty" );
        }
        return m_items.front( );
    }

    void
    pop( )
    {
        if ( m_items.empty( ) )
        {
            throw std::runtime_error( "heap is empty" );
        }
        m_items.front( ) = m_items.back( );
        m_items.resize( m_items.size( ) - 1 );
        heapify_down( );
    }

    void
    push( const T& elem )
    {
        m_items.push_back( elem );
        heapify_up( );
    }

    bool
    empty( ) const noexcept
    {
        return m_items.empty( );
    }

    typename Container::size_type
    size( ) const noexcept
    {
        return m_items.size( );
    }

private:
    void
    heapify_down( )
    {
        IndexType index = 0u;
        while ( has_left_child( index ) )
        {
            auto target_child_index
                = has_right_child( index )
                          && m_comparator( get_right_child( index ), get_left_child( index ) )
                      ? get_right_child_index( index )
                      : get_left_child_index( index );

            if ( m_comparator( m_items[ index ], m_items[ target_child_index ] ) )
            {
                break;
            }

            std::swap( m_items[ target_child_index ], m_items[ index ] );
            index = target_child_index;
        }
    }

    void
    heapify_up( )
    {
        auto index = m_items.size( ) - 1;
        while ( has_parent( index ) && m_comparator( m_items[ index ], get_parent( index ) ) )
        {
            std::swap( m_items[ get_parent_index( index ) ], m_items[ index ] );
            index = get_parent_index( index );
        }
    }

private:
    constexpr IndexType
    get_left_child_index( IndexType parent_index ) const noexcept
    {
        return 2 * parent_index + 1;
    }

    constexpr IndexType
    get_right_child_index( IndexType parent_index ) const noexcept
    {
        return 2 * parent_index + 2;
    }

    constexpr IndexType
    get_parent_index( IndexType child_index ) const noexcept
    {
        return ( child_index - 1 ) / 2;
    }

    constexpr bool
    has_left_child( IndexType parent_index ) const noexcept
    {
        return get_left_child_index( parent_index ) < m_items.size( );
    }

    constexpr bool
    has_right_child( IndexType parent_index ) const noexcept
    {
        return get_right_child_index( parent_index ) < m_items.size( );
    }

    constexpr bool
    has_parent( IndexType child_index ) const noexcept
    {
        return child_index > 0;
    }

    const T&
    get_left_child( IndexType parent_index ) const noexcept
    {
        return m_items[ get_left_child_index( parent_index ) ];
    }

    const T&
    get_right_child( IndexType parent_index ) const noexcept
    {
        return m_items[ get_right_child_index( parent_index ) ];
    }

    const T&
    get_parent( IndexType child_index ) const noexcept
    {
        return m_items[ get_parent_index( child_index ) ];
    }

private:
    const Compare m_comparator;
    Container m_items;
};
}  // namespace heap
