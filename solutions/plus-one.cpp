#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    plusOne( const vector< int >& digits )
    {
        auto res = digits;

        for ( int i = digits.size( ) - 1; i >= 0; --i )
        {
            if ( ++res[ i ] != 10 )
            {
                return res;
            }
            res[ i ] = 0;
        }

        res.insert( res.begin( ), 1 );
        return res;
    }
};
}  // namespace

TEST( PlusOne, generic )
{
    Solution sn;
    EXPECT_EQ( vector< int >( {1, 2, 4} ), sn.plusOne( vector< int >{1, 2, 3} ) );
    EXPECT_EQ( vector< int >( {4, 3, 2, 2} ), sn.plusOne( vector< int >{4, 3, 2, 1} ) );
    EXPECT_EQ( vector< int >( {1, 0} ), sn.plusOne( vector< int >{9} ) );
}
