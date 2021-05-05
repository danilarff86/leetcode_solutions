package gosolutions

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxArea(h int, w int, horizontalCuts []int, verticalCuts []int) int {
	sort.Ints(horizontalCuts)
	sort.Ints(verticalCuts)
	prevHor := 0
	prevVer := 0
	maxHor := 0
	maxVer := 0
	for _, c := range horizontalCuts {
		diff := c - prevHor
		if diff > maxHor {
			maxHor = diff
		}
		prevHor = c
	}
	for _, c := range verticalCuts {
		diff := c - prevVer
		if diff > maxVer {
			maxVer = diff
		}
		prevVer = c
	}
	diff := h - prevHor
	if diff > maxHor {
		maxHor = diff
	}
	diff = w - prevVer
	if diff > maxVer {
		maxVer = diff
	}
	return int(int64(maxHor) * int64(maxVer) % int64(1000000007))
}

func TestMaximumAreaOfAPieceOfCakeAfterHorizontalAndVerticalCuts(t *testing.T) {
	assert.Equal(t, 4, maxArea(5, 4, []int{1, 2, 3}, []int{1, 3}))
	assert.Equal(t, 6, maxArea(5, 4, []int{3, 1}, []int{1}))
	assert.Equal(t, 9, maxArea(5, 4, []int{3}, []int{1}))
}
