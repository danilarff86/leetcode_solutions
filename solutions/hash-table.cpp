#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
size_t
calculate_hash( const string& str )
{
    size_t value = 0;
    for ( size_t i = 0; i < str.length( ); i++ )
    {
        value = value * 37 + str[ i ];
    }

    return value;
}

template < typename Key, typename Val, size_t num_blocks = 1 << 8 >
struct MyHashTable
{
    static_assert( num_blocks && ( ( num_blocks & ( num_blocks - 1 ) ) == 0 ),
                   "num_blocks must be power of two" );

    using DataType = pair< const Key, Val >;

    MyHashTable( )
        : data_( num_blocks )
    {
    }

    bool
    insert( const DataType& data )
    {
        auto const hash_val = calculate_hash( data.first ) & ( num_blocks - 1 );
        auto& block = data_[ hash_val ];
        return block.insert( data ).second;
    }

    Val*
    find( const Key& key )
    {
        auto const hash_val = calculate_hash( key ) & ( num_blocks - 1 );
        auto& block = data_[ hash_val ];
        auto find_result = block.find( key );
        return find_result != block.end( ) ? &( find_result->second ) : nullptr;
    }

    bool
    remove( const Key& key )
    {
        auto const hash_val = calculate_hash( key ) & ( num_blocks - 1 );
        auto& block = data_[ hash_val ];
        return block.erase( key ) > 0;
    }

private:
    vector< map< Key, Val > > data_;
};
}  // namespace

TEST( HashTable, generic )
{
    MyHashTable< string, string, 1 << 8 > ht;
    EXPECT_TRUE( ht.insert( {"My", "Mother"} ) );
    EXPECT_FALSE( ht.insert( {"My", "Mother"} ) );
    EXPECT_TRUE( ht.insert( {"Her", "Father"} ) );
    auto res = ht.find( "My" );
    ASSERT_NE( nullptr, res );
    EXPECT_EQ( "Mother", *res );
    res = ht.find( "Her" );
    ASSERT_NE( nullptr, res );
    EXPECT_EQ( "Father", *res );
    EXPECT_TRUE( ht.remove( "Her" ) );
    res = ht.find( "Her" );
    ASSERT_EQ( nullptr, res );
    EXPECT_FALSE( ht.remove( "Her" ) );
}
