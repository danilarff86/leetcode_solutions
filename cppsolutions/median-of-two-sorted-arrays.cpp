#include "gtest/gtest.h"

#include <iterator>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    double
    findMedianSortedArrays( vector< int >& nums1, vector< int >& nums2 )
    {
        const auto common_length = nums1.size( ) + nums2.size( );
        const bool is_odd_length = common_length & 1;
        const auto advance_iterations = common_length / 2 - ( is_odd_length ? 0 : 1 );
        auto it1 = nums1.begin( );
        auto it2 = nums2.begin( );

        auto get_next = [&it1, &it2, &nums1, &nums2]( ) {
            if ( it1 != nums1.end( ) )
            {
                if ( it2 != nums2.end( ) )
                {
                    return *it1 < *it2 ? *it1++ : *it2++;
                }
                else
                {
                    return *it1++;
                }
            }
            else
            {
                return *it2++;
            }
        };

        for ( size_t i = 0; i < advance_iterations; i++ )
        {
            get_next( );
        }

        const auto median = get_next( );

        return is_odd_length ? median : ( median + get_next( ) ) / 2.0;
    }
};
}  // namespace

TEST( MedianOfTwoSortedArrays, generic )
{
    Solution sn;
    {
        vector< int > nums1{1, 3};
        vector< int > nums2{2};
        EXPECT_EQ( 2., sn.findMedianSortedArrays( nums1, nums2 ) );
    }
    {
        vector< int > nums1{1, 2};
        vector< int > nums2{3, 4};
        EXPECT_EQ( 2.5, sn.findMedianSortedArrays( nums1, nums2 ) );
    }
}
