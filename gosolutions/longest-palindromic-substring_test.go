package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func longestPalindrome(s string) string {
	sLen := len(s)
	if sLen == 0 {
		return ""
	}
	dp := make([][]bool, sLen)
	pStart := 0
	pLen := 1
	for i := 0; i < sLen; i++ {
		dp[i] = make([]bool, sLen)
		dp[i][i] = true
	}
	for i := 1; i < sLen; i++ {
		if s[i] == s[i-1] {
			dp[i-1][i] = true
			pLen = 2
			pStart = i - 1
		}
	}
	for sz := 3; sz <= sLen; sz++ {
		for first := 0; first < sLen-sz+1; first++ {
			last := first + sz - 1
			if s[first] == s[last] && dp[first+1][last-1] {
				dp[first][last] = true
				pLen = sz
				pStart = first
			}
		}
	}

	return s[pStart : pStart+pLen]
}

func TestLongestPalindromicSubstring(t *testing.T) {
	assert.Contains(t, []string{"bab", "aba"}, longestPalindrome("babad"))
	assert.Equal(t, "bb", longestPalindrome("cbbd"))
	assert.Equal(t, "a", longestPalindrome("a"))
	assert.Equal(t, "a", longestPalindrome("ac"))
	assert.Equal(t, "babababab", longestPalindrome("babababab"))
}
