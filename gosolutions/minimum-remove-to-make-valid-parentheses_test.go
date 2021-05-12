package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func minRemoveToMakeValid(s string) string {
	resultBytes := make([]rune, len(s))
	var stack []int
	for i, c := range s {
		resultBytes[i] = c
		switch c {
		case '(':
			stack = append(stack, i)
		case ')':
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			} else {
				resultBytes[i] = ' '
			}
		}
	}
	for _, i := range stack {
		resultBytes[i] = ' '
	}
	outIndex := 0
	for _, c := range resultBytes {
		if c != ' ' {
			resultBytes[outIndex] = c
			outIndex++
		}
	}

	return string(resultBytes[:outIndex])
}

func TestMinimumRemoveToMakeValidParentheses(t *testing.T) {
	assert.Contains(t, []string{"lee(t(c)o)de", "lee(t(co)de)", "lee(t(c)ode)"}, minRemoveToMakeValid("lee(t(c)o)de)"))
	assert.Equal(t, "ab(c)d", minRemoveToMakeValid("a)b(c)d"))
	assert.Equal(t, "", minRemoveToMakeValid("))(("))
	assert.Equal(t, "a(b(c)d)", minRemoveToMakeValid("(a(b(c)d)"))
}

func BenchmarkMinimumRemoveToMakeValidParentheses(b *testing.B) {
	for n := 0; n < b.N; n++ {
		minRemoveToMakeValid("lee(t(c)o)de)")
	}
}
