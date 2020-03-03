#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isScramble( const string& s1, const string& s2 )
    {
        memo.clear( );
        p_s1 = &s1;
        p_s2 = &s2;
        return isScrambleWithMemo( {0, 0, uint16_t( s1.size( ) )} );
    }

private:
    struct Key
    {
        uint16_t offset1;
        uint16_t offset2;
        uint16_t len;

        size_t
        operator( )( const Key& k ) const
        {
            size_t res = 17;
            res = res * 31 + k.offset1;
            res = res * 31 + k.offset2;
            res = res * 31 + k.len;
            return res;
        }

        bool
        operator( )( const Key& lhs, const Key& rhs ) const
        {
            return lhs.offset1 == rhs.offset1 && lhs.offset2 == rhs.offset2 && lhs.len == rhs.len;
        }
    };

    unordered_map< Key, bool, Key, Key > memo;
    const string* p_s1;
    const string* p_s2;

private:
    bool
    isScrambleWithMemo( const Key& key )
    {
        auto record = memo.find( key );
        if ( record != memo.end( ) )
        {
            return record->second;
        }

        if ( isEqueal( key ) )
        {
            memo[ key ] = true;
            return true;
        }

        for ( uint16_t i = 1u; i < key.len; i++ )
        {
            if ( isScrambleWithMemo( Key{key.offset1, key.offset2, i} )
                 && isScrambleWithMemo( Key{uint16_t( key.offset1 + i ),
                                            uint16_t( key.offset2 + i ),
                                            uint16_t( key.len - i )} ) )
            {
                memo[ key ] = true;
                return true;
            }

            if ( isScrambleWithMemo( {key.offset1, uint16_t( key.offset2 + ( key.len - i ) ), i} )
                 && isScrambleWithMemo(
                        {uint16_t( key.offset1 + i ), key.offset2, uint16_t( key.len - i )} ) )
            {
                memo[ key ] = true;
                return true;
            }
        }

        memo[ key ] = false;
        return false;
    }

    bool
    isEqueal( const Key& key )
    {
        for ( int i = 0; i < key.len; i++ )
        {
            if ( ( *p_s1 )[ i + key.offset1 ] != ( *p_s2 )[ i + key.offset2 ] )
            {
                return false;
            }
        }
        return true;
    }
};
}  // namespace

TEST( ScrambleString, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isScramble( "great", "rgeat" ) );
    EXPECT_FALSE( sn.isScramble( "abcde", "caebd" ) );
    EXPECT_TRUE( sn.isScramble( "abb", "bba" ) );
    EXPECT_TRUE( sn.isScramble( "abc", "bca" ) );
}
