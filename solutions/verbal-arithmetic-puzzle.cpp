#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace
{
class Solution
{
private:
    static const size_t NUM_DIGITS = 10;
    static const size_t NUM_SYMBOL_VALS = 0xFF;
    static const size_t UNMAPPED_SYMBOL_VAL = 0xFF;
    static const size_t MAPPED_SYMBOL_VAL = NUM_DIGITS;

    template < typename T, size_t SZ = NUM_DIGITS >
    struct StackContainer
    {
        T data[ SZ ];
        size_t size;
    };

public:
    bool
    isSolvable( const vector< string >& words, const string& result )
    {
        char_mapping_ = vector< uint8_t >( NUM_SYMBOL_VALS, UNMAPPED_SYMBOL_VAL );
        allocated_digits_ = 0;

        words_ = &words;
        result_ = &result;

        size_t word_max_len = 0;

        for ( const auto& word : words )
        {
            if ( word.size( ) > word_max_len )
            {
                word_max_len = word.size( );
            }
        }

        if ( result.size( ) > word_max_len + 1 )
        {
            return false;
        }

        last_index = max( result.size( ), word_max_len );

        return is_solvable_recursive( 1, 0 );
    }

private:
    bool
    is_solvable_recursive( const int right_index, const int words_carry )
    {
        if ( right_index > last_index )
        {
            return words_carry == 0;
        }

        StackContainer< int8_t > free_digits;
        fill_free_digits( free_digits );

        StackContainer< uint8_t > unmapped_symbols;
        fill_unmapped_symbols( unmapped_symbols, right_index );

        do
        {
            apply_arrangement( free_digits, unmapped_symbols );

            int next_words_carry;
            if ( is_solvable_at_index( right_index, words_carry, next_words_carry ) )
            {
                mark_digits_assigned( free_digits.data, unmapped_symbols.size );
                auto recursive_res = is_solvable_recursive( right_index + 1, next_words_carry );
                mark_digits_unassigned( free_digits.data, unmapped_symbols.size );
                if ( recursive_res )
                {
                    return true;
                }
            }
        } while ( next_arrangement( free_digits.data, free_digits.size, unmapped_symbols.size ) );

        mark_symbols_unmapped( unmapped_symbols );
        return false;
    }

private:
    inline void
    mark_symbols_unmapped( const StackContainer< uint8_t >& unmapped_symbols )
    {
        for ( size_t i = 0; i < unmapped_symbols.size; i++ )
        {
            char_mapping_[ unmapped_symbols.data[ i ] ] = UNMAPPED_SYMBOL_VAL;
        }
    }

    inline void
    mark_digits_assigned( int8_t* digits, size_t size )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            allocated_digits_ |= 1 << digits[ i ];
        }
    }

    inline void
    mark_digits_unassigned( int8_t* digits, size_t size )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            allocated_digits_ &= ~( 1 << digits[ i ] );
        }
    }

    inline void
    fill_free_digits( StackContainer< int8_t >& free_digits ) const
    {
        free_digits.size = 0;
        ;
        for ( size_t i = 0; i < NUM_DIGITS; i++ )
        {
            if ( ( ( 1 << i ) & allocated_digits_ ) == 0 )
            {
                free_digits.data[ free_digits.size++ ] = i;
            }
        }
    }

    inline void
    fill_unmapped_symbols( StackContainer< uint8_t >& unmapped_symbols, const int right_index )
    {
        unmapped_symbols.size = 0;
        for ( const auto& word : *words_ )
        {
            if ( word.size( ) >= right_index )
            {
                const auto c = word[ word.size( ) - right_index ];
                if ( char_mapping_[ c ] == UNMAPPED_SYMBOL_VAL )
                {
                    char_mapping_[ c ] = MAPPED_SYMBOL_VAL;
                    unmapped_symbols.data[ unmapped_symbols.size++ ] = c;
                }
            }
        }

        if ( result_->size( ) >= right_index )
        {
            const auto c = ( *result_ )[ result_->size( ) - right_index ];
            if ( char_mapping_[ c ] == UNMAPPED_SYMBOL_VAL )
            {
                char_mapping_[ c ] = MAPPED_SYMBOL_VAL;
                unmapped_symbols.data[ unmapped_symbols.size++ ] = c;
            }
        }
    }

    inline void
    apply_arrangement( const StackContainer< int8_t >& arrangement,
                       const StackContainer< uint8_t >& symbols )
    {
        for ( size_t i = 0; i < symbols.size; i++ )
        {
            char_mapping_[ symbols.data[ i ] ] = arrangement.data[ i ];
        }
    }

    static inline bool
    next_arrangement( int8_t* a, int n, int m )
    {
        int j;
        do
        {
            j = n - 2;
            while ( j >= 0 && a[ j ] >= a[ j + 1 ] )
            {
                j--;
            }

            if ( j < 0 )
            {
                return false;
            }

            int k = n - 1;
            while ( a[ j ] >= a[ k ] )
            {
                k--;
            }

            swap( a[ j ], a[ k ] );
            int l = j + 1, r = n - 1;
            while ( l < r )
            {
                swap( a[ l++ ], a[ r-- ] );
            }

        } while ( j > m - 1 );
        return true;
    }

    inline bool
    is_solvable_at_index( const int right_index,
                          const int words_carry,
                          int& next_words_carry ) const
    {
        int words_sum = words_carry;
        for ( const auto& word : *words_ )
        {
            if ( word.size( ) >= right_index )
            {
                const auto c = word[ word.size( ) - right_index ];
                const auto char_val = char_mapping_[ c ];
                if ( word.size( ) == right_index && char_val == 0 )
                {
                    return false;
                }
                words_sum += char_val;
            }
        }

        if ( result_->size( ) < right_index )
        {
            return false;
        }

        const auto result_val = char_mapping_[ ( *result_ )[ result_->size( ) - right_index ] ];

        if ( result_->size( ) == right_index && result_val == 0 )
        {
            return false;
        }

        const bool res = ( result_val % NUM_DIGITS ) == ( words_sum % NUM_DIGITS );
        if ( res )
        {
            next_words_carry = words_sum / NUM_DIGITS;
        }

        return res;
    }

private:
    vector< uint8_t > char_mapping_;
    uint16_t allocated_digits_;
    const vector< string >* words_;
    const string* result_;
    size_t last_index;
};
}  // namespace

TEST( VerbalArithmeticPuzzle, generic )
{
    Solution sn;
    EXPECT_TRUE( sn.isSolvable( {"SEND", "MORE"}, "MONEY" ) );
    EXPECT_TRUE( sn.isSolvable( {"SIX", "SEVEN", "SEVEN"}, "TWENTY" ) );
    EXPECT_TRUE( sn.isSolvable( {"THIS", "IS", "TOO"}, "FUNNY" ) );
    EXPECT_FALSE( sn.isSolvable( {"LEET", "CODE"}, "POINT" ) );
    EXPECT_FALSE( sn.isSolvable( {"TO", "BE", "OR", "NOT"}, "TOBE" ) );
    EXPECT_TRUE( sn.isSolvable( {"THAT", "IS", "WHY", "IT", "IS"}, "TRUE" ) );
    EXPECT_FALSE( sn.isSolvable( {"AB", "CD", "EF"}, "GHIJ" ) );
}
