package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func merge(nums1 []int, m int, nums2 []int, n int) {
	for i := m - 1; i >= 0; i-- {
		nums1[i+n] = nums1[i]
	}

	i1 := n
	i2 := 0
	i := 0
	for i1 < (m+n) && i2 < n {
		if nums1[i1] < nums2[i2] {
			nums1[i] = nums1[i1]
			i1++
		} else {
			nums1[i] = nums2[i2]
			i2++
		}
		i++
	}

	for ; i1 < (m + n); i1++ {
		nums1[i] = nums1[i1]
		i++
	}

	for ; i2 < n; i2++ {
		nums1[i] = nums2[i2]
		i++
	}
}

func TestMergeSortedArray(t *testing.T) {
	{
		nums1 := []int{1, 2, 3, 0, 0, 0}
		nums2 := []int{2, 5, 6}
		merge(nums1, len(nums1)-len(nums2), nums2, len(nums2))

		assert.Equal(t, []int{1, 2, 2, 3, 5, 6}, nums1)
	}
	{
		nums1 := []int{1}
		nums2 := []int{}
		merge(nums1, len(nums1)-len(nums2), nums2, len(nums2))

		assert.Equal(t, []int{1}, nums1)
	}
	{
		nums1 := []int{4, 0, 0, 0, 0, 0}
		nums2 := []int{1, 2, 3, 5, 6}
		merge(nums1, len(nums1)-len(nums2), nums2, len(nums2))

		assert.Equal(t, []int{1, 2, 3, 4, 5, 6}, nums1)
	}
}
