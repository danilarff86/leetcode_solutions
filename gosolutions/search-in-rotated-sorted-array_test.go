package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func search(nums []int, target int) int {
	start := 0
	end := len(nums) - 1
	for start <= end {
		mid := start + (end-start)/2
		if nums[start] <= nums[mid] {
			if target >= nums[start] && target <= nums[mid] {
				end = mid
			} else {
				start = mid + 1
			}
		} else {
			if target >= nums[mid+1] && target <= nums[end] {
				start = mid + 1
			} else {
				end = mid
			}
		}
		if start == end {
			if target == nums[start] {
				return start
			} else {
				return -1
			}
		}
	}
	return -1
}

func TestSearchInRotatedSortedArray(t *testing.T) {
	assert.Equal(t, 4, search([]int{4, 5, 6, 7, 0, 1, 2}, 0))
	assert.Equal(t, -1, search([]int{4, 5, 6, 7, 0, 1, 2}, 3))
	assert.Equal(t, -1, search([]int{1}, 0))
}

func BenchmarkSearchInRotatedSortedArray(b *testing.B) {
	for n := 0; n < b.N; n++ {
		search([]int{4, 5, 6, 7, 0, 1, 2}, 0)
	}
}
