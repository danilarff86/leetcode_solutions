package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func removeDuplicateLettersStolen(s string) string {
	var frequency ['z' - 'a' + 1]int
	var visited ['z' - 'a' + 1]bool
	for _, c := range s {
		frequency[c-'a']++
	}

	stack := make([]rune, 0, len(s))
	for _, c := range s {
		frequency[c-'a']--
		if visited[c-'a'] {
			continue
		}

		for len(stack) > 0 {
			cTop := stack[len(stack)-1]
			if c >= cTop || frequency[cTop-'a'] == 0 {
				break
			}

			visited[cTop-'a'] = false
			stack = stack[:len(stack)-1]
		}

		stack = append(stack, c)
		visited[c-'a'] = true
	}

	return string(stack)
}

func removeDuplicateLetters(s string) string {
	var lastIndex ['z' - 'a' + 1]int
	var added ['z' - 'a' + 1]bool
	for i, c := range s {
		lastIndex[c-'a'] = i
	}

	stack := make([]rune, 0, len(s))
	for i, c := range s {
		if added[c-'a'] {
			continue
		}

		for len(stack) > 0 {
			cTop := stack[len(stack)-1]
			if c >= cTop || lastIndex[cTop-'a'] < i {
				break
			}

			stack = stack[:len(stack)-1]
			added[cTop-'a'] = false
		}

		stack = append(stack, c)
		added[c-'a'] = true
	}

	return string(stack)
}

func TestRemoveDuplicateLetters(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    string
		expected string
	}{
		{
			name:     "Example 1",
			input:    "bcabc",
			expected: "abc",
		},
		{
			name:     "Example 2",
			input:    "cbacdcbc",
			expected: "acdb",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, removeDuplicateLetters(tc.input))
			assert.Equal(t, tc.expected, removeDuplicateLettersStolen(tc.input))
		})
	}
}
