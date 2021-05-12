package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func generateParenthesisHelper(opened int, closed int, current []rune, result *[]string) {
	if (opened + closed) == len(current) {
		*result = append(*result, string(current))
		return
	}
	if opened < (len(current) / 2) {
		cur := current
		cur[opened+closed] = '('
		generateParenthesisHelper(opened+1, closed, cur, result)
	}
	if closed < opened {
		current[opened+closed] = ')'
		generateParenthesisHelper(opened, closed+1, current, result)
	}
}

func generateParenthesis(n int) []string {
	var result []string
	generateParenthesisHelper(0, 0, make([]rune, n*2), &result)
	return result
}

func TestGenerateParentheses(t *testing.T) {
	assert.Equal(t, []string{"((()))", "(()())", "(())()", "()(())", "()()()"}, generateParenthesis(3))
	assert.Equal(t, []string{"()"}, generateParenthesis(1))
}

func BenchmarkGenerateParentheses(b *testing.B) {
	for n := 0; n < b.N; n++ {
		generateParenthesis(5)
	}
}
