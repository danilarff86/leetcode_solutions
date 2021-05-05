package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func productExceptSelf(nums []int) []int {
	res := make([]int, len(nums))
	res[0] = nums[0]
	for i := 1; i < len(nums) - 1; i++ {
		res[i] = res[i-1] * nums[i]
	}
	res[len(nums) - 1] = res[len(nums)-2]

	rightMul := nums[len(nums)-1]
	for i := len(nums) - 2; i > 0; i-- {
		res[i] = res[i-1] * rightMul
		rightMul *= nums[i]
	}
	res[0] = rightMul

	return res
}

func TestProductOfArrayExceptSelf(t *testing.T) {
	assert.Equal(t, []int{24, 12, 8, 6}, productExceptSelf([]int{1, 2, 3, 4}))
	assert.Equal(t, []int{0, 0, 9, 0, 0}, productExceptSelf([]int{-1, 1, 0, -3, 3}))
}

func BenchmarkProductOfArrayExceptSelf(b *testing.B) {
	for n := 0; n < b.N; n++ {
		productExceptSelf([]int{1, 2, 3, 4})
	}
}
