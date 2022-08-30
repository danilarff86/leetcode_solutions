package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func numDecodingsTopDown(s string) int {
	var dp func(sub string) int
	dp = func(sub string) int {
		if len(sub) == 0 {
			return 1
		}
		if sub[0] == '0' {
			return 0
		}

		res := 0
		if len(sub) > 1 && (sub[0] == '1' || (sub[0] == '2' && sub[1] <= '6')) {
			res += dp(sub[2:])
		}
		res += dp(sub[1:])
		return res
	}

	return dp(s)
}

func numDecodings(s string) int {
	dp := make([]int, len(s)+1)
	dp[len(s)] = 1
	if s[len(s)-1] != '0' {
		dp[len(s)-1] = 1
	}
	for i := len(s) - 2; i >= 0; i-- {
		if s[i] != '0' {
			dp[i] += dp[i+1]
			if s[i] == '1' || (s[i] == '2' && s[i+1] <= '6') {
				dp[i] += dp[i+2]
			}
		}
	}
	return dp[0]
}

func TestDecodeWays(t *testing.T) {
	assert.Equal(t, 2, numDecodingsTopDown("12"))
	assert.Equal(t, 3, numDecodingsTopDown("226"))
	assert.Equal(t, 0, numDecodingsTopDown("06"))
	assert.Equal(t, 1, numDecodingsTopDown("10"))

	assert.Equal(t, 2, numDecodings("12"))
	assert.Equal(t, 3, numDecodings("226"))
	assert.Equal(t, 0, numDecodings("06"))
	assert.Equal(t, 1, numDecodings("10"))
}
