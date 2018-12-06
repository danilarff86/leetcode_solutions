#include <cstdlib>
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
    for ( ; s_offset < end_offset; )
    {
        *buf++ = s_buf[ s_offset++ ];
    }

    return s_offset - initial_offset;
}

class Solution
{
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int
    read( char* buf, int n )
    {
        int read_chars = 0;
        int last_chunk = 4;
        while ( read_chars < n && last_chunk == 4 )
        {
            last_chunk = read4( buf + read_chars );
            read_chars += last_chunk;
        }

        return min( n, read_chars );
    }
};
}  // namespace

TEST( ReadNCharactersGivenRead4, generic )
{
    Solution sn;
    char buf[ 1024 ];

    set_buf( "abc" );
    EXPECT_EQ( "abc", string( buf, sn.read( buf, 4 ) ) );

    set_buf( "abcde" );
    EXPECT_EQ( "abcde", string( buf, sn.read( buf, 5 ) ) );
}
