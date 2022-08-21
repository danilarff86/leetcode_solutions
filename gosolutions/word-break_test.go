package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func wordBreak(s string, wordDict []string) bool {
	dict := make(map[string]struct{})
	for _, w := range wordDict {
		dict[w] = struct{}{}
	}
	dp := make([]bool, len(s)+1)
	dp[0] = true
	for i := 1; i <= len(s); i++ {
		for j := 0; j <= i; j++ {
			if dp[j] {
				_, ok := dict[s[j:i]]
				if ok {
					dp[i] = true
					break
				}
			}
		}
	}
	return dp[len(s)]
}

func wordBreakDP2(s string, wordDict []string) bool {
	dict := make(map[string]struct{})
	for _, w := range wordDict {
		dict[w] = struct{}{}
	}
	dp := make([]bool, len(s)+1)
	dp[0] = true
	for i := 1; i <= len(s); i++ {
		for j := i - 1; j >= 0; j-- {
			if dp[j] {
				_, ok := dict[s[j:i]]
				if ok {
					dp[i] = true
					break
				}
			}
		}
	}
	return dp[len(s)]
}

func TestWordBreak(t *testing.T) {
	assert.True(t, wordBreak("leetcode", []string{"leet", "code"}))
	assert.True(t, wordBreak("applepenapple", []string{"apple", "pen"}))
	assert.False(t, wordBreak("catsandog", []string{"cats", "dog", "sand", "and", "cat"}))

	assert.True(t, wordBreakDP2("leetcode", []string{"leet", "code"}))
	assert.True(t, wordBreakDP2("applepenapple", []string{"apple", "pen"}))
	assert.False(t, wordBreakDP2("catsandog", []string{"cats", "dog", "sand", "and", "cat"}))
}
