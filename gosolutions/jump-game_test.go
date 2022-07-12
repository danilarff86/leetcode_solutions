package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

// func canJump(nums []int) bool {
// 	validPosition := make([]bool, len(nums))
// 	validPosition[0] = true

// 	for i := 0; i < len(nums); i++ {
// 		if !validPosition[i] {
// 			continue
// 		}

// 		maxJump := i + nums[i]
// 		if maxJump >= len(nums) {
// 			maxJump = len(nums) - 1
// 		}

// 		for j := i + 1; j <= maxJump; j++ {
// 			validPosition[j] = true
// 		}
// 	}

// 	return validPosition[len(nums)-1]
// }

func canJump(nums []int) bool {
	n := len(nums)
	jumpLength := 1
	i := 0

	for ; i < n; i++ {
		jumpLength--
		if nums[i] > jumpLength {
			jumpLength = nums[i]
		} else if jumpLength == 0 {
			break
		}
	}

	return i >= n-1
}

func TestCanJump(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    []int
		expected bool
	}{
		{
			name:     "Example 1",
			input:    []int{2, 3, 1, 1, 4},
			expected: true,
		},
		{
			name:     "Example 2",
			input:    []int{3, 2, 1, 0, 4},
			expected: false,
		},
		{
			name:     "Example 3",
			input:    []int{0},
			expected: true,
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, canJump(tc.input))
		})
	}
}
