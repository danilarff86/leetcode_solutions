#include "gtest/gtest.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

namespace
{
namespace sequence1
{
class Solution
{
public:
    int
    recursive_article( int n )
    {
        if ( n == 0 || n == 1 )
        {
            return 1;  // Проверка на начальное значение
        }

        if ( n % 2 == 0 )
        {  //Проверка на чётность
            return recursive_article( n / 2 )
                   + recursive_article( n / 2 - 1 );  // Вычисляем по формуле для чётных индексов,
                                                      //  ссылаясь на предыдущие значения
        }
        else
        {
            return recursive_article( ( n - 1 ) / 2 )
                   - recursive_article( ( n - 1 ) / 2 - 1 );  // Вычисляем по формуле для нечётных
                                                              //индексов, ссылаясь на предыдущие
                                                              //значения
        }
    }

    int
    recursive_mine( int n )
    {
        if ( n <= 1 )
        {
            return 1;
        }

        const auto half = n / 2;
        const auto half_res = recursive_mine( half );
        const auto half_minus_1_res = recursive_mine( half - 1 );
        return ( n & 1 ) ? ( half_res - half_minus_1_res ) : ( half_res + half_minus_1_res );
    }

    int
    recursive_with_memo_mine( int n )
    {
        unordered_map< int, int > memo;

        function< int( int ) > recursive_fn = [&]( int n ) {
            int val;
            if ( memo.find( n ) == memo.end( ) )
            {
                if ( n <= 1 )
                {
                    val = 1;
                }
                else
                {
                    const auto half = n / 2;
                    const auto half_res = recursive_fn( half );
                    const auto half_minus_1_res = recursive_fn( half - 1 );
                    val = ( n & 1 ) ? ( half_res - half_minus_1_res )
                                    : ( half_res + half_minus_1_res );
                }

                memo[ n ] = val;
                return val;
            }
            return memo[ n ];
        };

        return recursive_fn( n );
    }

    int
    dp_article( int n )
    {
        if ( n < 2 )  //Может, нам и вычислять ничего не нужно?
        {
            return 1;
        }

        vector< int > fs( n );  //Создаём массив для значений
        fs[ 0 ] = fs[ 1 ] = 1;  //Задаём начальные состояния

        for ( int i = 2; i < n; i++ )
        {
            if ( i % 2 == 0 )  //Проверяем чётность
            {
                fs[ i ] = fs[ i / 2 ] + fs[ i / 2 - 1 ];
            }
            else
            {
                fs[ i ] = fs[ ( i - 1 ) / 2 ] - fs[ ( i - 1 ) / 2 - 1 ];
            }
        }

        return fs[ n - 1 ];
    }

    int
    indices_stack_article( int n )
    {
        queue< int > q;
        stack< int > s;

        s.push( n );
        q.push( n );
        int dum;

        while ( !q.empty( ) )
        {  //Пока есть что вычислять
            dum = q.front( );
            q.pop( );

            if ( dum % 2 == 0 )
            {  //Проверяем чётность
                if ( dum / 2 > 1 )
                {  //Если вычисленная зависимость не принадлежит начальным состояниям
                    s.push( dum / 2 );  //Добавляем в стек
                    q.push( dum / 2 );  //Сохраняем, чтобы
                                        //вычислить дальнейшие зависимости
                }
                if ( dum / 2 - 1 > 1 )
                {  //Проверяем принадлежность к начальным состояниям
                    s.push( dum / 2 - 1 );  //Добавляем в стек
                    q.push( dum / 2 - 1 );  //Сохрнаяем, чтобы
                                            //вычислить дальнейшие зависимости
                }
            }
            else
            {
                if ( ( dum - 1 ) / 2 > 1 )
                {  //Проверяем принадлежность к начальным состояниям
                    s.push( ( dum - 1 ) / 2 );  //Добавляем в стек
                    q.push( ( dum - 1 ) / 2 );  //Сохрнаяем, чтобы
                                                //вычислить дальнейшие зависимости
                }
                if ( ( dum - 1 ) / 2 - 1 > 1 )
                {  //Проверяем принадлежность к начальным состояниям
                    s.push( ( dum - 1 ) / 2 - 1 );  //Добавляем в стек
                    q.push( ( dum - 1 ) / 2 - 1 );  //Сохрнаяем, чтобы
                                                    //вычислить дальнейшие зависимости
                }
            }

            /*
            Конкретно для этой задачи есть более элегантный способ найти все зависимости,
            здесь же показан достаточно универсальный
            */
        }

        unordered_map< int, int > values;
        values[ 0 ] = 1;  //Важно добавить начальные состояния
        //в таблицу значений
        values[ 1 ] = 1;

        while ( !s.empty( ) )
        {
            int num = s.top( );
            s.pop( );

            if ( values.find( num ) == values.end( ) )
            {  //Эту конструкцию
               //вы должны помнить с абзаца о кешировании
                if ( num % 2 == 0 )
                {  //Проверяем чётность
                    int value = values[ num / 2 ] + values[ num / 2 - 1 ];  //Вычисляем значение
                    values[ num ] = value;  //Помещаем его в таблицу
                }
                else
                {
                    int value = values[ ( num - 1 ) / 2 ]
                                - values[ ( num - 1 ) / 2 - 1 ];  //Вычисляем значение
                    values[ num ] = value;  //Помещаем его в таблицу
                }
            }
        }

        return values[ n ];
    }

    int
    indices_stack_mine( int n )
    {
        queue< int > q;
        stack< int > s;

        s.push( n );
        q.push( n );

        while ( !q.empty( ) )
        {
            const auto val = q.front( );
            q.pop( );

            const auto half = val / 2;
            if ( half > 1 )
            {
                s.push( half );
                q.push( half );

                const auto half_minus_1 = val / 2 - 1;
                if ( half_minus_1 > 1 )
                {
                    s.push( half_minus_1 );
                    q.push( half_minus_1 );
                }
            }
        }

        unordered_map< int, int > memo{{0, 1}, {1, 1}};

        while ( !s.empty( ) )
        {
            int num = s.top( );
            s.pop( );

            if ( memo.find( num ) == memo.end( ) )
            {
                const auto half = num / 2;
                const auto half_res = memo[ half ];
                const auto half_minus_1_res = memo[ half - 1 ];
                memo[ num ] = ( num & 1 ) ? ( half_res - half_minus_1_res )
                                          : ( half_res + half_minus_1_res );
            }
        }

        return memo[ n ];
    }
};
}  // namespace sequence1

namespace ball
{
class Solution
{
public:
    int
    recursive_article( int n )
    {
        if ( n == 1 )
            return 1;
        if ( n == 2 )
            return 2;
        if ( n == 3 )
            return 4;

        return recursive_article( n - 1 ) + recursive_article( n - 2 ) + recursive_article( n - 3 );
    }

    int
    recursive_mine( int n )
    {
        return n > 3
                   ? ( recursive_mine( n - 1 ) + recursive_mine( n - 2 ) + recursive_mine( n - 3 ) )
                   : ( n == 3 ) ? 4 : n;
    }

    int
    dp_mine( int n )
    {
        vector< int > dp( n + 1 );
        dp[ 1 ] = 1;
        dp[ 2 ] = 2;
        dp[ 3 ] = 4;
        for ( size_t i = 4; i <= n; i++ )
        {
            dp[ i ] = dp[ i - 1 ] + dp[ i - 2 ] + dp[ i - 3 ];
        }
        return dp[ n ];
    }

    int
    dp_mine_low_mem( int n )
    {
        vector< int > dp{4, 1, 2};
        for ( size_t i = 4; i <= n; i++ )
        {
            dp[ i % 3 ] = dp[ 0 ] + dp[ 1 ] + dp[ 2 ];
        }
        return dp[ n % 3 ];
    }
};
}  // namespace ball

namespace path
{
class Solution
{
public:
    int
    recursive_article( int i, int j )
    {
        if ( i == 1 || j == 1 )
        {
            return 1;
        }

        return recursive_article( i - 1, j ) + recursive_article( i, j - 1 );
    }

    int
    recursive_mine( int i, int j )
    {
        if ( i == 1 || j == 1 )
        {
            return 1;
        }

        return recursive_mine( i, j - 1 ) + recursive_mine( i - 1, j );
    }

    int
    dp_mine( int i_res, int j_res )
    {
        vector< vector< int > > dp( i_res + 1, vector< int >( j_res + 1, 1 ) );

        for ( size_t i = 2; i <= i_res; i++ )
        {
            for ( size_t j = 2; j <= i_res; j++ )
            {
                dp[ i ][ j ] = dp[ i ][ j - 1 ] + dp[ i - 1 ][ j ];
            }
        }

        return dp[ i_res ][ j_res ];
    }

    int
    dp_mine_1d( int i_res, int j_res )
    {
        vector< int > dp( j_res + 1, 1 );

        for ( size_t i = 2; i <= i_res; i++ )
        {
            for ( size_t j = 2; j <= i_res; j++ )
            {
                dp[ j ] += dp[ j - 1 ];
            }
        }

        return dp[ j_res ];
    }
};
}  // namespace path

namespace stairs
{
class Solution
{
public:
    int
    dp_article( const vector< int >& prices )
    {
        auto dp = prices;

        for ( int i = 2; i < dp.size( ); i++ )
        {
            dp[ i ] += min( dp[ i - 1 ], dp[ i - 2 ] );
        }

        return dp.back( );
    }

    int
    recursive_mine( const vector< int >& prices )
    {
        function< int( int ) > recursive_fn = [&]( int n ) {
            if ( n < 2 )
            {
                return prices[ n ];
            }
            return prices[ n ] + min( recursive_fn( n - 1 ), recursive_fn( n - 2 ) );
        };

        return recursive_fn( prices.size( ) - 1 );
    }
};
}  // namespace stairs

namespace calc
{
class Solution
{
public:
    tuple< int, string >
    dp_article( int n )
    {
        vector< int > a( n + 1 );
        a[ 1 ] = 0;

        {
            int min;
            for ( int i = 2; i < n + 1; i++ )
            {
                min = a[ i - 1 ] + 1;
                if ( i % 2 == 0 )
                    min = std::min( min, a[ i / 2 ] + 1 );
                if ( i % 3 == 0 )
                    min = std::min( min, a[ i / 3 ] + 1 );

                a[ i ] = min;
            }
        }

        string ret;

        {
            int i = n;
            while ( i > 1 )
            {
                if ( a[ i ] == a[ i - 1 ] + 1 )
                {
                    ret.insert( 0, "1" );
                    i--;
                    continue;
                }

                if ( i % 2 == 0 && a[ i ] == a[ i / 2 ] + 1 )
                {
                    ret.insert( 0, "2" );
                    i /= 2;
                    continue;
                }

                ret.insert( 0, "3" );
                i /= 3;
            }
        }

        return make_tuple( a[ n ], move( ret ) );
    }

    tuple< int, string >
    recursive_mine( int n )
    {
        if ( n < 2 )
        {
            return {};
        }

        int res_cost;
        string res_seq;
        char res_char = '1';

        std::tie( res_cost, res_seq ) = recursive_mine( n - 1 );

        if ( !( n % 2 ) )
        {
            int tmp_cost;
            string tmp_seq;

            std::tie( tmp_cost, tmp_seq ) = recursive_mine( n / 2 );

            if ( tmp_cost < res_cost )
            {
                res_cost = tmp_cost;
                res_seq = move( tmp_seq );
                res_char = '2';
            }
        }

        if ( !( n % 3 ) )
        {
            int tmp_cost;
            string tmp_seq;

            std::tie( tmp_cost, tmp_seq ) = recursive_mine( n / 3 );

            if ( tmp_cost < res_cost )
            {
                res_cost = tmp_cost;
                res_seq = move( tmp_seq );
                res_char = '3';
            }
        }

        res_seq.push_back( res_char );

        return make_tuple( res_cost + 1, move( res_seq ) );
    }

    tuple< int, string >
    dp_mine( int n )
    {
        vector< int > dp_val( n + 1 );
        vector< int > dp_op( n + 1 );
        for ( size_t i = 2; i <= n; i++ )
        {
            auto min_val = dp_val[ i - 1 ];
            int op = 1;

            if ( i % 2 == 0 )
            {
                const auto val = dp_val[ i / 2 ];
                if ( val < min_val )
                {
                    min_val = val;
                    op = 2;
                }
            }
            if ( i % 3 == 0 )
            {
                const auto val = dp_val[ i / 3 ];
                if ( val < min_val )
                {
                    min_val = val;
                    op = 3;
                }
            }

            dp_val[ i ] = min_val + 1;
            dp_op[ i ] = op;
        }

        string op_str;
        int val = n;
        while ( val > 1 )
        {
            const auto op = dp_op[ val ];
            op_str.push_back( op + '0' );
            if ( op == 1 )
            {
                --val;
            }
            else
            {
                val /= op;
            }
        }

        std::reverse( op_str.begin( ), op_str.end( ) );

        return make_tuple( dp_val[ n ], move( op_str ) );
    }
};
}  // namespace calc

namespace food
{
class Solution
{
public:
    int
    dp_article( const vector< vector< int > >& cell_cost )
    {
        auto dp = cell_cost;

        for ( int i = 0; i < cell_cost.size( ); i++ )
        {
            for ( int j = 0; j < cell_cost[ 0 ].size( ); j++ )
            {
                if ( i > 0 && j > 0 )
                {
                    dp[ i ][ j ] += min( dp[ i - 1 ][ j ], dp[ i ][ j - 1 ] );
                }
                else
                {
                    if ( i > 0 )
                    {
                        dp[ i ][ j ] += dp[ i - 1 ][ j ];
                    }
                    else if ( j > 0 )
                    {
                        dp[ i ][ j ] += dp[ i ][ j - 1 ];
                    }
                }
            }
        }

        return dp.back( ).back( );
    }

    int
    dp_mine( const vector< vector< int > >& cell_cost )
    {
        auto dp = cell_cost;

        {
            dp.insert( dp.begin( ),
                       vector< int >( cell_cost[ 0 ].size( ), numeric_limits< int >::max( ) ) );
            for ( auto& row : dp )
            {
                row.insert( row.begin( ), numeric_limits< int >::max( ) );
            }
            dp[ 0 ][ 1 ] = dp[ 1 ][ 0 ] = 0;
        }

        for ( size_t i = 1; i < dp.size( ); i++ )
        {
            for ( size_t j = 1; j < dp.size( ); j++ )
            {
                dp[ i ][ j ] += min( dp[ i ][ j - 1 ], dp[ i - 1 ][ j ] );
            }
        }

        return dp.back( ).back( );
    }
};
}  // namespace food

}  // namespace

TEST( DPTutorial, sequence1_recursive_article )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.recursive_article( 10 ) );
    EXPECT_EQ( 7, sn.recursive_article( 20 ) );
}

TEST( DPTutorial, sequence1_recursive_mine )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.recursive_mine( 10 ) );
    EXPECT_EQ( 7, sn.recursive_mine( 20 ) );
}

TEST( DPTutorial, sequence1_recursive_with_memo_mine )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.recursive_with_memo_mine( 10 ) );
    EXPECT_EQ( 7, sn.recursive_with_memo_mine( 20 ) );
}

TEST( DPTutorial, DISABLED_sequence1_dp_article )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.dp_article( 10 ) );
    EXPECT_EQ( 7, sn.dp_article( 20 ) );
}

TEST( DPTutorial, sequence1_indices_stack_article )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.indices_stack_article( 10 ) );
    EXPECT_EQ( 7, sn.indices_stack_article( 20 ) );
}

TEST( DPTutorial, sequence1_indices_stack_mine )
{
    sequence1::Solution sn;
    EXPECT_EQ( 4, sn.indices_stack_mine( 10 ) );
    EXPECT_EQ( 7, sn.indices_stack_mine( 20 ) );
}

TEST( DPTutorial, DISABLED_ball_recursive_article )
{
    ball::Solution sn;
    EXPECT_EQ( 13, sn.recursive_article( 5 ) );
    EXPECT_EQ( 274, sn.recursive_article( 10 ) );
    EXPECT_EQ( 53798080, sn.recursive_article( 30 ) );
}

TEST( DPTutorial, DISABLED_ball_recursive_mine )
{
    ball::Solution sn;
    EXPECT_EQ( 13, sn.recursive_mine( 5 ) );
    EXPECT_EQ( 274, sn.recursive_mine( 10 ) );
    EXPECT_EQ( 53798080, sn.recursive_mine( 30 ) );
}

TEST( DPTutorial, ball_dp_mine )
{
    ball::Solution sn;
    EXPECT_EQ( 13, sn.dp_mine( 5 ) );
    EXPECT_EQ( 274, sn.dp_mine( 10 ) );
    EXPECT_EQ( 53798080, sn.dp_mine( 30 ) );
}

TEST( DPTutorial, ball_dp_mine_low_mem )
{
    ball::Solution sn;
    EXPECT_EQ( 13, sn.dp_mine_low_mem( 5 ) );
    EXPECT_EQ( 274, sn.dp_mine_low_mem( 10 ) );
    EXPECT_EQ( 53798080, sn.dp_mine_low_mem( 30 ) );
}

TEST( DPTutorial, path_recursive_article )
{
    path::Solution sn;
    EXPECT_EQ( 70, sn.recursive_article( 5, 5 ) );
}

TEST( DPTutorial, path_recursive_mine )
{
    path::Solution sn;
    EXPECT_EQ( 70, sn.recursive_mine( 5, 5 ) );
}

TEST( DPTutorial, path_dp_mine )
{
    path::Solution sn;
    EXPECT_EQ( 70, sn.dp_mine( 5, 5 ) );
}

TEST( DPTutorial, path_dp_mine_1d )
{
    path::Solution sn;
    EXPECT_EQ( 70, sn.dp_mine_1d( 5, 5 ) );
}

TEST( DPTutorial, stairs_dp_article )
{
    stairs::Solution sn;
    EXPECT_EQ( 19, sn.dp_article( {7, 3, 4, 5, 2, 10, 14, 1} ) );
}

TEST( DPTutorial, stairs_recursive_mine )
{
    stairs::Solution sn;
    EXPECT_EQ( 19, sn.recursive_mine( {7, 3, 4, 5, 2, 10, 14, 1} ) );
}

TEST( DPTutorial, calc_dp_article )
{
    calc::Solution sn;
    EXPECT_EQ( make_tuple( 3, string( "331" ) ), sn.dp_article( 10 ) );
    EXPECT_EQ( make_tuple( 7, string( "3311331" ) ), sn.dp_article( 100 ) );
}

TEST( DPTutorial, calc_recursive_mine )
{
    calc::Solution sn;
    EXPECT_EQ( make_tuple( 3, string( "331" ) ), sn.recursive_mine( 10 ) );
    EXPECT_EQ( make_tuple( 7, string( "3311331" ) ), sn.recursive_mine( 100 ) );
}

TEST( DPTutorial, calc_dp_mine )
{
    calc::Solution sn;
    EXPECT_EQ( make_tuple( 3, string( "331" ) ), sn.dp_mine( 10 ) );
    EXPECT_EQ( make_tuple( 7, string( "3311331" ) ), sn.dp_mine( 100 ) );
}

TEST( DPTutorial, food_dp_article )
{
    food::Solution sn;
    EXPECT_EQ( 208, sn.dp_article( {{10, 24, 13, 4, 15},
                                    {11, 43, 56, 12, 3},
                                    {2, 12, 34, 32, 56},
                                    {15, 23, 75, 23, 56},
                                    {21, 45, 54, 23, 67}} ) );
}

TEST( DPTutorial, food_dp_mine )
{
    food::Solution sn;
    EXPECT_EQ( 208, sn.dp_mine( {{10, 24, 13, 4, 15},
                                 {11, 43, 56, 12, 3},
                                 {2, 12, 34, 32, 56},
                                 {15, 23, 75, 23, 56},
                                 {21, 45, 54, 23, 67}} ) );
}