#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    vector< int >
    sortArrayByParityII( const vector< int >& A )
    {
        vector< int > res( A.size( ) );
        int i_odd = 0;
        int i_even = 0;
        int i = 0;
        while ( i < A.size( ) )
        {
            while ( A[ i_even ] & 1 )
            {
                ++i_even;
            }
            while ( !( A[ i_odd ] & 1 ) )
            {
                ++i_odd;
            }
            res[ i++ ] = A[ i_even++ ];
            res[ i++ ] = A[ i_odd++ ];
        }
        return res;
    }
};
}  // namespace

TEST( ArrayByParityII, generic )
{
    Solution sn;
    EXPECT_EQ( ( vector< int >{4, 5, 2, 7} ), sn.sortArrayByParityII( {4, 2, 5, 7} ) );
}
