package gosolutions

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func twoOutOfThree(nums1 []int, nums2 []int, nums3 []int) []int {
	var hash [101]int

	for _, n := range nums1 {
		hash[n] = 1
	}
	for _, n := range nums2 {
		hash[n] |= 1 << 1
	}
	for _, n := range nums3 {
		hash[n] |= 1 << 2
	}

	var res []int
	for i, v := range hash {
		if v > 4 || v == 3 {
			res = append(res, i)
		}
	}

	return res
}

func twoOutOfThreeArrays(nums1 []int, nums2 []int, nums3 []int) []int {
	var (
		hash1 [101]int
		hash2 [101]int
		hash3 [101]int
	)

	for _, n := range nums1 {
		hash1[n] = 1
	}
	for _, n := range nums2 {
		hash2[n] = 1
	}
	for _, n := range nums3 {
		hash3[n] = 1
	}

	var res []int
	for i := 1; i < 101; i++ {
		if hash1[i]+hash2[i]+hash3[i] > 1 {
			res = append(res, i)
		}
	}

	return res
}

func twoOutOfThreeMap(nums1 []int, nums2 []int, nums3 []int) []int {
	hash := map[int]int{}

	for _, n := range nums1 {
		hash[n] = 1
	}
	for _, n := range nums2 {
		hash[n] |= 1 << 1
	}
	for _, n := range nums3 {
		hash[n] |= 1 << 2
	}

	var res []int
	for i, v := range hash {
		if v > 4 || v == 3 {
			res = append(res, i)
		}
	}

	return res
}

func TestTwoOutOfThree(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    [3][]int
		expected []int
	}{
		{
			name: "Example 1",
			input: [3][]int{
				{1, 1, 3, 2},
				{2, 3},
				{3},
			},
			expected: []int{2, 3},
		},
		{
			name: "Example 2",
			input: [3][]int{
				{3, 1},
				{2, 3},
				{1, 2},
			},
			expected: []int{1, 2, 3},
		},
		{
			name: "Example 3",
			input: [3][]int{
				{1, 2, 2},
				{4, 3, 3},
				{5},
			},
			expected: nil,
		},
		{
			name: "Example 4",
			input: [3][]int{
				{2, 15, 10, 11, 14, 12, 14, 11, 9, 1},
				{8, 9, 13, 2, 11, 8},
				{13, 5, 15, 7, 12, 7, 8, 3, 13, 15},
			},
			expected: []int{2, 8, 9, 11, 12, 13, 15},
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, twoOutOfThree(tc.input[0], tc.input[1], tc.input[2]))
			assert.Equal(t, tc.expected, twoOutOfThreeArrays(tc.input[0], tc.input[1], tc.input[2]))
			actual := twoOutOfThreeMap(tc.input[0], tc.input[1], tc.input[2])
			sort.Ints(actual)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
