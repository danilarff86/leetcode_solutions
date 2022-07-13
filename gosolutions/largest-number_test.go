package gosolutions

import (
	"sort"
	"strconv"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

func largestNumber(nums []int) string {
	strNums := make([]string, 0, len(nums))
	for _, num := range nums {
		strNums = append(strNums, strconv.Itoa(num))
	}

	sort.Slice(strNums, func(i, j int) bool {
		lhs, rhs := strNums[i], strNums[j]

		return lhs+rhs > rhs+lhs
	})

	if strNums[0] == "0" {
		return "0"
	}

	return strings.Join(strNums, "")
}

func TestLargestNumber(t *testing.T) {
	for _, tc := range []struct {
		name     string
		nums     []int
		expected string
	}{
		{
			name:     "Example 1",
			nums:     []int{10, 2},
			expected: "210",
		},
		{
			name:     "Example 2",
			nums:     []int{3, 30, 34, 5, 9},
			expected: "9534330",
		},
		{
			name:     "Example 3",
			nums:     []int{0, 0},
			expected: "0",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, largestNumber(tc.nums))
		})
	}
}
