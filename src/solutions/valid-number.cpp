#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
public:
    bool
    isNumber( string s )
    {
        auto cit = s.begin( );

        // Skip leading spaces
        while ( cit != s.end( ) && isspace( *cit ) )
        {
            ++cit;
        }

        bool power_symbol_occured = false;
        bool decimal_symbol_occured = false;
        bool digits_occured = false;

        while ( cit != s.end( ) && !isspace( *cit ) )
        {
            switch ( *cit )
            {
            case 'e':
                if ( !digits_occured || power_symbol_occured )
                {
                    return false;
                }
                power_symbol_occured = true;
                digits_occured = false;
                break;
            case '.':
                if ( decimal_symbol_occured || power_symbol_occured )
                {
                    return false;
                }
                decimal_symbol_occured = true;
                break;
            case '-':
            case '+':
                if ( digits_occured || ( decimal_symbol_occured && !power_symbol_occured ) )
                {
                    return false;
                }
                break;
            default:
                if ( !isdigit( *cit ) )
                {
                    return false;
                }
                digits_occured = true;
                break;
            }
            ++cit;
        }

        // Skip trailing spaces
        while ( cit != s.end( ) && isspace( *cit ) )
        {
            ++cit;
        }

        return digits_occured && cit == s.end( );
    }
};
}  // namespace

TEST( ValidNumber, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isNumber( "0" ) );
    EXPECT_TRUE( sn.isNumber( " 0.1 " ) );
    EXPECT_FALSE( sn.isNumber( "abc" ) );
    EXPECT_FALSE( sn.isNumber( "1 a" ) );
    EXPECT_TRUE( sn.isNumber( "2e10" ) );
    EXPECT_FALSE( sn.isNumber( "e" ) );
    EXPECT_FALSE( sn.isNumber( "e9" ) );
    EXPECT_TRUE( sn.isNumber( "-1." ) );
    EXPECT_FALSE( sn.isNumber( "6e6.5" ) );
    EXPECT_TRUE( sn.isNumber( " 005047e+6" ) );
    EXPECT_FALSE( sn.isNumber( ".-4" ) );
}
