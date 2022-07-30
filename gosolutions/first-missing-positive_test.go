package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func firstMissingPositive(nums []int) int {
	sz := len(nums)

	for i, n := range nums {
		if n <= 0 {
			nums[i] = sz + 1
		}
	}

	for _, n := range nums {
		if n < 0 {
			n *= -1
		}
		n -= 1
		if n < sz && nums[n] > 0 {
			nums[n] *= -1
		}
	}

	res := 0
	for res < sz && nums[res] < 0 {
		res++
	}
	return res + 1
}

func TestFirstMissingPositive(t *testing.T) {
	for _, tc := range []struct {
		name     string
		nums     []int
		expected int
	}{
		{
			name:     "Example 1",
			nums:     []int{1, 2, 0},
			expected: 3,
		},
		{
			name:     "Example 2",
			nums:     []int{3, 4, -1, 1},
			expected: 2,
		},
		{
			name:     "Example 3",
			nums:     []int{7, 8, 9, 11, 12},
			expected: 1,
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, firstMissingPositive(tc.nums))
		})
	}
}
