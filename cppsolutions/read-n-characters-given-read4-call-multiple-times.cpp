#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
static string s_buf;
static size_t s_offset;

void
set_buf( const string& str )
{
    s_buf = str;
    s_offset = 0;
}

int
read4( char* buf )
{
    const auto initial_offset = s_offset;
    const auto end_offset = min( s_buf.size( ), s_offset + 4 );
    while ( s_offset < end_offset )
    {
        *buf++ = s_buf[ s_offset++ ];
    }

    return s_offset - initial_offset;
}

class Solution
{
public:
    Solution( )
        : last_chunk_size( 0 )
        , last_chunk_offset( 0 )
    {
    }

    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int
    read( char* buf, int n )
    {
        int read_chars = 0;

        auto end_chunk_offset = min( size_t( n + last_chunk_offset ), last_chunk_size );
        while ( last_chunk_offset < end_chunk_offset )
        {
            *buf++ = last_chunk_buf[ last_chunk_offset++ ];
            ++read_chars;
        }

        int last_chunk = 4;
        while ( read_chars < n && last_chunk == 4 )
        {
            last_chunk = read4( last_chunk_buf );
            last_chunk_size = last_chunk;
            last_chunk_offset = 0;

            auto end_chunk_offset = min( size_t( n - read_chars ), last_chunk_size );
            while ( last_chunk_offset < end_chunk_offset )
            {
                *buf++ = last_chunk_buf[ last_chunk_offset++ ];
                ++read_chars;
            }
        }

        return read_chars;
    }

private:
    size_t last_chunk_size;
    size_t last_chunk_offset;
    char last_chunk_buf[ 4 ];
};
}  // namespace

TEST( ReadNCharactersGivenRead4CallMultipleTimes, generic )
{
    char buf[ 1024 ];

    unique_ptr< Solution > sln( new Solution );
    set_buf( "abc" );
    EXPECT_EQ( "a", string( buf, sln->read( buf, 1 ) ) );
    EXPECT_EQ( "bc", string( buf, sln->read( buf, 2 ) ) );
    EXPECT_EQ( "", string( buf, sln->read( buf, 1 ) ) );

    sln.reset( new Solution );
    set_buf( "abc" );
    EXPECT_EQ( "abc", string( buf, sln->read( buf, 4 ) ) );
    EXPECT_EQ( "", string( buf, sln->read( buf, 1 ) ) );
}
