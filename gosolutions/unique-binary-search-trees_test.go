package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func numTreesDP(n int) int {
	dp := make([]int, n+1)
	dp[0] = 1
	dp[1] = 1
	for i := 2; i <= n; i++ {
		val := 0
		for j := 1; j <= i; j++ {
			val += dp[j-1] * dp[i-j]
		}
		dp[i] = val
	}
	return dp[n]
}

func numTrees(n int) int {
	res := 1
	for i := 2; i <= n; i++ {
		res = (4*i - 2) * res / (i + 1)
	}
	return res
}

func TestUniqueBinarySearchTreesDP(t *testing.T) {
	assert.Equal(t, 1, numTreesDP(1))
	assert.Equal(t, 2, numTreesDP(2))
	assert.Equal(t, 5, numTreesDP(3))
	assert.Equal(t, 14, numTreesDP(4))
	assert.Equal(t, 42, numTreesDP(5))
}

func TestUniqueBinarySearchTrees(t *testing.T) {
	assert.Equal(t, 1, numTrees(1))
	assert.Equal(t, 2, numTrees(2))
	assert.Equal(t, 5, numTrees(3))
	assert.Equal(t, 14, numTrees(4))
	assert.Equal(t, 42, numTrees(5))
}
