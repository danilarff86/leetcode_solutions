#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace zero_alloc
{
class Solution
{
public:
    vector< int >
    findMinHeightTrees( int n, const vector< vector< int > >& edges )
    {
        vector< vector< int > > graph( n );
        for ( auto& node : graph )
        {
            node.reserve( n - 1 );
        }
        for ( const auto& edge : edges )
        {
            graph[ edge[ 0 ] ].push_back( edge[ 1 ] );
            graph[ edge[ 1 ] ].push_back( edge[ 0 ] );
        }
        m_leaves.resize( n );
        std::fill( m_leaves.begin( ), m_leaves.end( ), 0 );
        auto leaves_count = fill_leaves( graph );
        auto iteration = 1;
        while ( leaves_count < n )
        {
            leaves_count += remove_leaves( graph, ++iteration );
        }

        vector< int > res;
        for ( size_t i = 0; i < n; ++i )
        {
            if ( m_leaves[ i ] == iteration )
            {
                res.push_back( i );
            }
        }

        return res;
    }

private:
    int
    fill_leaves( vector< vector< int > >& graph )
    {
        int leaves_cnt = 0;
        for ( size_t i = 0; i < graph.size( ); ++i )
        {
            auto& node = graph[ i ];
            if ( node.size( ) <= 1 )
            {
                m_leaves[ i ] = 1;
                ++leaves_cnt;
            }
        }
        return leaves_cnt;
    }

    int
    remove_leaves( vector< vector< int > >& graph, int iteration )
    {
        int new_leaves_cnt = 0;
        for ( size_t i = 0; i < graph.size( ); ++i )
        {
            auto& node = graph[ i ];
            int sz = node.size( );
            for ( int j = node.size( ) - 1; j >= 0; --j )
            {
                const auto leaves_val = m_leaves[ node[ j ] ];
                if ( leaves_val && leaves_val < iteration )
                {
                    node[ j ] = node[ --sz ];
                }
            }
            node.resize( sz );
            if ( sz <= 1 && m_leaves[ i ] == 0 )
            {
                m_leaves[ i ] = iteration;
                ++new_leaves_cnt;
            }
        }
        return new_leaves_cnt;
    }

private:
    vector< int > m_leaves;
};
}  // namespace zero_alloc

namespace fast
{
class Solution
{
public:
    vector< int >
    findMinHeightTrees( int n, const vector< vector< int > >& edges )
    {
        vector< pair< size_t, vector< int >* > > graph( n );
        for ( size_t i = 0; i < n; ++i )
        {
            graph[ i ] = make_pair( i, new vector< int >( ) );
            graph[ i ].second->reserve( n - 1 );
        }
        for ( const auto& edge : edges )
        {
            graph[ edge[ 0 ] ].second->push_back( edge[ 1 ] );
            graph[ edge[ 1 ] ].second->push_back( edge[ 0 ] );
        }

        vector< int > leaves( n );
        int leaves_cnt = 0;

        {
            int sz_graph = graph.size( );
            for ( int i = graph.size( ) - 1; i >= 0; --i )
            {
                if ( graph[ i ].second->size( ) <= 1 )
                {
                    leaves[ graph[ i ].first ] = 1;
                    ++leaves_cnt;
                    delete graph[ i ].second;
                    graph[ i ] = graph[ --sz_graph ];
                }
            }
            graph.resize( sz_graph );
        }

        int iteration = 1;
        while ( leaves_cnt < n )
        {
            ++iteration;
            int sz_graph = graph.size( );
            for ( int i = graph.size( ) - 1; i >= 0; --i )
            {
                auto& node = *graph[ i ].second;
                int sz_node = node.size( );
                for ( int j = node.size( ) - 1; j >= 0; --j )
                {
                    const auto leaves_val = leaves[ node[ j ] ];
                    if ( leaves_val && leaves_val < iteration )
                    {
                        node[ j ] = node[ --sz_node ];
                    }
                }
                node.resize( sz_node );
                if ( sz_node <= 1 && leaves[ graph[ i ].first ] == 0 )
                {
                    leaves[ graph[ i ].first ] = iteration;
                    ++leaves_cnt;
                    delete graph[ i ].second;
                    graph[ i ] = graph[ --sz_graph ];
                }
            }
            graph.resize( sz_graph );
        }

        vector< int > res;
        for ( size_t i = 0; i < n; ++i )
        {
            if ( leaves[ i ] == iteration )
            {
                res.push_back( i );
            }
        }

        return res;
    }
};
}  // namespace fast

TEST( MinimumHeightTrees, generic )
{
    {
        zero_alloc::Solution sn;
        EXPECT_EQ( ( vector< int >{1} ), sn.findMinHeightTrees( 4, {{1, 0}, {1, 2}, {1, 3}} ) );
        EXPECT_EQ( ( vector< int >{3, 4} ),
                   sn.findMinHeightTrees( 6, {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}} ) );
    }
    {
        fast::Solution sn;
        EXPECT_EQ( ( vector< int >{1} ), sn.findMinHeightTrees( 4, {{1, 0}, {1, 2}, {1, 3}} ) );
        EXPECT_EQ( ( vector< int >{3, 4} ),
                   sn.findMinHeightTrees( 6, {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}} ) );
    }
}
