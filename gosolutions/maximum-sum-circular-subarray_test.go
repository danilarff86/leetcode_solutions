package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxSubarraySumCircular(nums []int) int {
	n := len(nums)
	res, cur := nums[0], nums[0]
	for i := 1; i < n; i++ {
		cur += nums[i]
		if nums[i] > cur {
			cur = nums[i]
		}
		if cur > res {
			res = cur
		}
	}

	maxright := make([]int, n)
	maxright[n-1] = nums[n-1]
	cur = nums[n-1]
	for i := n - 2; i >= 0; i-- {
		cur += nums[i]
		maxright[i] = maxright[i+1]
		if cur > maxright[i] {
			maxright[i] = cur
		}
	}

	leftsum := 0
	for i := 0; i < n-1; i++ {
		leftsum += nums[i]
		cur = leftsum + maxright[i+1]
		if cur > res {
			res = cur
		}
	}

	return res
}

func TestMaximumSumCircularSubarray(t *testing.T) {
	assert.Equal(t, 3, maxSubarraySumCircular([]int{1, -2, 3, -2}))
	assert.Equal(t, 10, maxSubarraySumCircular([]int{5, -3, 5}))
	assert.Equal(t, -2, maxSubarraySumCircular([]int{-3, -2, -3}))
}
