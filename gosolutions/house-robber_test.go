package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func max(x, y int) int {
	if x < y {
		return y
	}
	return x
}

func rob(nums []int) int {
	elements := len(nums)

	dp := make([]int, elements+2)
	for i := 0; i < elements; i++ {
		dp[i+2] = max(dp[i+1], dp[i]+nums[i])
	}
	return dp[elements+1]
}

func TestHouseRobber(t *testing.T) {
	assert.Equal(t, 4, rob([]int{1, 2, 3, 1}))
	assert.Equal(t, 12, rob([]int{2, 7, 9, 3, 1}))
}
