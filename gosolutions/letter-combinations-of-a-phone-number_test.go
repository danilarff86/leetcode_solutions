package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func letterCombinations(digits string) []string {
	var mappedLetters []string = []string{
		"abc",
		"def",
		"ghi",
		"jkl",
		"mno",
		"pqrs",
		"tuv",
		"wxyz",
	}

	numDigits := len(digits)
	combination := make([]byte, numDigits)

	res := []string{}

	var doCalculate func(index int)
	doCalculate = func(index int) {
		if index >= numDigits {
			res = append(res, string(combination))
			return
		}

		d := int(digits[index] - byte('2'))

		for _, letter := range mappedLetters[d] {
			combination[index] = byte(letter)
			doCalculate(index + 1)
		}
	}

	if numDigits > 0 {
		doCalculate(0)
	}

	return res
}

func TestLetterCombinationsOfAPhoneNumber(t *testing.T) {
	assert.Equal(t, []string{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}, letterCombinations("23"))
	assert.Equal(t, []string{}, letterCombinations(""))
	assert.Equal(t, []string{"a", "b", "c"}, letterCombinations("2"))
}
