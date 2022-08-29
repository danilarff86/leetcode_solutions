package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func numWaysDP(n int, k int) int {
	if n <= 1 {
		return k
	}

	dp := make([]int, n)
	dp[0] = k
	dp[1] = k * k

	for i := 2; i < n; i++ {
		dp[i] = (k - 1) * (dp[i-1] + dp[i-2])
	}

	return dp[n-1]
}

func numWays(n int, k int) int {
	if n <= 1 {
		return k
	}

	oneBefore, twoBefore := k*k, k

	for i := 2; i < n; i++ {
		tmp := oneBefore
		oneBefore = (k - 1) * (oneBefore + twoBefore)
		twoBefore = tmp
	}

	return oneBefore
}

func TestPaintFence(t *testing.T) {
	assert.Equal(t, 6, numWaysDP(3, 2))
	assert.Equal(t, 42, numWaysDP(7, 2))
	assert.Equal(t, 1, numWaysDP(1, 1))
	assert.Equal(t, 9, numWaysDP(2, 3))

	assert.Equal(t, 6, numWays(3, 2))
	assert.Equal(t, 42, numWays(7, 2))
	assert.Equal(t, 1, numWays(1, 1))
	assert.Equal(t, 9, numWays(2, 3))
}
