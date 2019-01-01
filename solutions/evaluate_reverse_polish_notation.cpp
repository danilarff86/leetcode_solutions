#include "gtest/gtest.h"

#include <functional>
#include <stack>
#include <vector>

using namespace std;

namespace
{
class Solution
{
public:
    int
    evalRPN( const vector< string >& tokens )
    {
        stack< int > work_mem;

        const auto& plus_op = plus< int >( );
        const auto& minus_op = minus< int >( );
        const auto& multiplies_op = multiplies< int >( );
        const auto& divides_op = divides< int >( );
        static const auto perform_operatin
            = [&work_mem]( const function< int( int, int ) >& operation ) {
                  const auto operand_2 = work_mem.top( );
                  work_mem.pop( );
                  const auto operand_1 = work_mem.top( );
                  work_mem.pop( );
                  work_mem.push( operation( operand_1, operand_2 ) );
              };

        for ( const auto token : tokens )
        {
            if ( token.size( ) == 1 )
            {
                switch ( token[ 0 ] )
                {
                case '+':
                    perform_operatin( plus_op );
                    break;
                case '-':
                    perform_operatin( minus_op );
                    break;
                case '*':
                    perform_operatin( multiplies_op );
                    break;
                case '/':
                    perform_operatin( divides_op );
                    break;
                default:
                    work_mem.push( stoi( token ) );
                    break;
                }
            }
            else
            {
                work_mem.push( stoi( token ) );
            }
        }
        return work_mem.top( );
    }
};
}  // namespace

TEST( EvaluateReversePolishNotation, generic )
{
    Solution sn;
    EXPECT_EQ( 9, sn.evalRPN( {"2", "1", "+", "3", "*"} ) );
    EXPECT_EQ( 6, sn.evalRPN( {"4", "13", "5", "/", "+"} ) );
    EXPECT_EQ(
        22, sn.evalRPN( {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"} ) );
}
