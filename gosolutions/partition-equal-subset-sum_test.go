package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func canPartition_2dp(nums []int) bool {
	targetSum := 0
	for _, n := range nums {
		targetSum += n
	}
	if targetSum&1 == 1 {
		return false
	}
	targetSum >>= 1

	dp := make([][]bool, len(nums)+1)
	dp[len(nums)] = make([]bool, targetSum+1)
	dp[len(nums)][0] = true
	for i := len(nums) - 1; i >= 0; i-- {
		dp[i] = make([]bool, targetSum+1)
		dp[i][0] = true
		for j := 1; j <= targetSum; j++ {
			dp[i][j] = dp[i+1][j]
			if !dp[i][j] && j >= nums[i] {
				dp[i][j] = dp[i+1][j-nums[i]]
			}
		}
	}

	return dp[0][targetSum]
}

func canPartition(nums []int) bool {
	targetSum := 0
	for _, n := range nums {
		targetSum += n
	}
	if targetSum&1 == 1 {
		return false
	}
	targetSum >>= 1

	dp := make([]bool, targetSum+1)
	dp[0] = true
	for i := len(nums) - 1; i >= 0 && !dp[targetSum]; i-- {
		for j := targetSum; j > 0; j-- {
			if !dp[j] && j >= nums[i] {
				dp[j] = dp[j-nums[i]]
			}
		}
	}

	return dp[targetSum]
}

func TestPartitionEqualSubsetSum(t *testing.T) {
	for _, tc := range []struct {
		name     string
		nums     []int
		expected bool
	}{
		{
			name:     "Example 1",
			nums:     []int{1, 5, 11, 5},
			expected: true,
		},
		{
			name:     "Example 2",
			nums:     []int{1, 2, 3, 5},
			expected: false,
		},
		{
			name:     "Example 3",
			nums:     []int{2, 2, 1, 1},
			expected: true,
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, canPartition(tc.nums))
		})
	}
}
