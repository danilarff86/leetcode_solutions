package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func lengthOfLIS(nums []int) int {
	dp := make([]int, len(nums))
	dp[0] = 1
	res := 1
	for i := 1; i < len(nums); i++ {
		dp[i] = 1
		v := nums[i]
		for j := 0; j < i; j++ {
			if nums[j] < v && dp[j]+1 > dp[i] {
				dp[i] = dp[j] + 1
			}
		}
		if dp[i] > res {
			res = dp[i]
		}
	}

	return res
}

func TestLongestIncreasingSubsequence(t *testing.T) {
	assert.Equal(t, 4, lengthOfLIS([]int{10, 9, 2, 5, 3, 7, 101, 18}))
	assert.Equal(t, 4, lengthOfLIS([]int{0, 1, 0, 3, 2, 3}))
	assert.Equal(t, 1, lengthOfLIS([]int{7, 7, 7, 7, 7, 7, 7}))
	assert.Equal(t, 6, lengthOfLIS([]int{1, 3, 6, 7, 9, 4, 10, 5, 6}))
}
