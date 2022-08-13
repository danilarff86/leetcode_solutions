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
	if len(nums) > 1 && nums[0] > nums[1] {
		nums[1] = nums[0]
	}

	for i := 2; i < len(nums); i++ {
		nums[i] = max(nums[i-1], nums[i-2]+nums[i])
	}

	return nums[len(nums)-1]
}

func TestHouseRobber(t *testing.T) {
	assert.Equal(t, 4, rob([]int{1, 2, 3, 1}))
	assert.Equal(t, 12, rob([]int{2, 7, 9, 3, 1}))
}
