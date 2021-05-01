package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func longestPalindrome(s string) string {
	dp := make([][]bool, len(s))
	pStart := 0
	pLen := 0
	if len(s) > 0 {
		pLen = 1
	}
	for i := 0; i < len(s); i++ {
		dp[i] = make([]bool, len(s))
		dp[i][i] = true
	}
	for i := 1; i < len(s); i++ {
		val := (s[i] == s[i-1])
		dp[i-1][i] = val
		if val && pLen < 2 {
			pLen = 2
			pStart = i - 1
		}
	}

	for sz := 3; sz <= len(s); sz++ {
		for i := 0; i < len(s)-sz+1; i++ {
			val := s[i] == s[i+sz-1] && dp[i+1][i+sz-2]
			dp[i][i+sz-1] = val
			if val && pLen < sz {
				pLen = sz
				pStart = i
			}
		}
	}

	return s[pStart : pStart+pLen]
}

func TestLongestPalindromicSubstring(t *testing.T) {
	assert.Equal(t, "bab", longestPalindrome("babad"))
	assert.Equal(t, "bb", longestPalindrome("cbbd"))
	assert.Equal(t, "a", longestPalindrome("a"))
	assert.Equal(t, "a", longestPalindrome("ac"))
	assert.Equal(t, "babababab", longestPalindrome("babababab"))
}
