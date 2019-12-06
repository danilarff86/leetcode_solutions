#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    string
    countAndSay( int n )
    {
        if ( n > 1 )
        {
            auto s = countAndSay( n - 1 );
            string res;
            res.reserve( s.size( ) * 2 );
            int offset = 0;
            while ( offset < s.size( ) )
            {
                auto cnt = count_digits( s, offset );
                res.push_back( char( cnt ) + '0' );
                res.push_back( s[ offset ] );
                offset += cnt;
            }
            return res;
        }
        else
        {
            return "1";
        }
    }

private:
    int
    count_digits( const string& s, int offset )
    {
        int cnt = 1;
        const char digit = s[ offset++ ];
        while ( offset < s.size( ) && digit == s[ offset ] )
        {
            ++offset;
            ++cnt;
        }
        return cnt;
    }
};
}  // namespace

TEST( CountAndSay, generic )
{
    Solution sn;
    EXPECT_EQ( "1", sn.countAndSay( 1 ) );
    EXPECT_EQ( "11", sn.countAndSay( 2 ) );
    EXPECT_EQ( "21", sn.countAndSay( 3 ) );
    EXPECT_EQ( "1211", sn.countAndSay( 4 ) );
    EXPECT_EQ( "111221", sn.countAndSay( 5 ) );
}
