package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maximumScoreRecursive(nums []int, multipliers []int) int {
	n, m := len(nums), len(multipliers)
	memo := make([][]int, m)
	for i := 0; i < m; i++ {
		memo[i] = make([]int, m)
	}
	var recursive func(left, i int) int
	recursive = func(left, i int) int {
		if i >= m {
			return 0
		}

		if memo[left][i] == 0 {
			v1 := nums[left]*multipliers[i] + recursive(left+1, i+1)
			right := i - left
			v2 := nums[n-1-right]*multipliers[i] + recursive(left, i+1)
			memo[left][i] = max(v1, v2)
		}
		return memo[left][i]
	}

	return recursive(0, 0)
}

func maximumScore(nums []int, multipliers []int) int {
	n, m := len(nums), len(multipliers)
	dp := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]int, m+1)
	}

	if len(multipliers) == 0 {
		return 0
	}

	for i := m - 1; i >= 0; i-- {
		for left := 0; left <= i; left++ {
			v1 := nums[left]*multipliers[i] + dp[i+1][left+1]
			v2 := nums[n-1-(i-left)]*multipliers[i] + dp[i+1][left]
			dp[i][left] = max(v1, v2)
		}
	}

	return dp[0][0]
}

func TestMaximumScoreFromPerformingMultiplicationOperations(t *testing.T) {
	assert.Equal(t, 14, maximumScoreRecursive([]int{1, 2, 3}, []int{3, 2, 1}))
	assert.Equal(t, 102, maximumScoreRecursive([]int{-5, -3, -3, -2, 7, 1}, []int{-10, -5, 3, 4, 6}))

	assert.Equal(t, 14, maximumScore([]int{1, 2, 3}, []int{3, 2, 1}))
	assert.Equal(t, 102, maximumScore([]int{-5, -3, -3, -2, 7, 1}, []int{-10, -5, 3, 4, 6}))
}
