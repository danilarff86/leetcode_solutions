package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func tribonacci(n int) int {
	if n < 3 {
		if n < 1 {
			return 0
		}
		return 1
	}

	dp := make([]int, n+1)
	dp[1] = 1
	dp[2] = 1

	for i := 3; i <= n; i++ {
		dp[i] = dp[i-1] + dp[i-2] + dp[i-3]
	}

	return dp[n]
}

func TestNthTribonacciNumber(t *testing.T) {
	assert.Equal(t, 4, tribonacci(4))
	assert.Equal(t, 1389537, tribonacci(25))
}
