package gosolutions

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func deleteAndEarn(nums []int) int {
	weights := make(map[int]int)
	for _, num := range nums {
		weights[num] += num
	}
	nums = make([]int, 0, len(weights))
	for k, _ := range weights {
		nums = append(nums, k)
	}
	sort.Ints(nums)
	dp1, dp2 := 0, weights[nums[0]]
	for i := 1; i < len(nums); i++ {
		weight := weights[nums[i]]
		if nums[i]-nums[i-1] > 1 {
			dp1, dp2 = dp2, dp2+weight
		} else {
			dp1, dp2 = dp2, max(dp2, dp1+weight)
		}
	}

	return dp2
}

func TestDeleteAndEarn(t *testing.T) {
	assert.Equal(t, 6, deleteAndEarn([]int{3, 4, 2}))
	assert.Equal(t, 9, deleteAndEarn([]int{2, 2, 3, 3, 3, 4}))
	assert.Equal(t, 18, deleteAndEarn([]int{1, 1, 1, 2, 4, 5, 5, 5, 6}))
}
