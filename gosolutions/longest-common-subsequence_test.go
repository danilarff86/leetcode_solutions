package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func longestCommonSubsequenceTopDown(text1 string, text2 string) int {
	l1 := len(text1)
	l2 := len(text2)

	memo := make([][]int, l1)
	for i := 0; i < l1; i++ {
		memo[i] = make([]int, l2)
		for j := 0; j < l2; j++ {
			memo[i][j] = -1
		}
	}

	var dp func(i, j int) int
	dp = func(i, j int) int {
		if i >= l1 || j >= l2 {
			return 0
		}

		if memo[i][j] < 0 {
			if text1[i] == text2[j] {
				memo[i][j] = dp(i+1, j+1) + 1
			} else {
				memo[i][j] = max(dp(i+1, j), dp(i, j+1))
			}
		}

		return memo[i][j]
	}

	return dp(0, 0)
}

func longestCommonSubsequence(text1 string, text2 string) int {
	l1 := len(text1)
	l2 := len(text2)

	dp := make([][]int, l1+1)
	for i := 0; i <= l1; i++ {
		dp[i] = make([]int, l2+1)
	}

	for i := l1 - 1; i >= 0; i-- {
		for j := l2 - 1; j >= 0; j-- {
			if text1[i] == text2[j] {
				dp[i][j] = dp[i+1][j+1] + 1
			} else {
				dp[i][j] = max(dp[i+1][j], dp[i][j+1])
			}
		}
	}

	return dp[0][0]
}

func TestLongestCommonSubsequence(t *testing.T) {
	assert.Equal(t, 3, longestCommonSubsequenceTopDown("abcde", "ace"))
	assert.Equal(t, 3, longestCommonSubsequenceTopDown("ace", "ace"))
	assert.Equal(t, 0, longestCommonSubsequenceTopDown("abc", "def"))
	assert.Equal(t, 1, longestCommonSubsequenceTopDown("bsbininm", "jmjkbkjkv"))

	assert.Equal(t, 3, longestCommonSubsequence("abcde", "ace"))
	assert.Equal(t, 3, longestCommonSubsequence("ace", "ace"))
	assert.Equal(t, 0, longestCommonSubsequence("abc", "def"))
	assert.Equal(t, 1, longestCommonSubsequence("bsbininm", "jmjkbkjkv"))
}
