package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type highest struct {
	left  int
	right int
}

func (h highest) min() int {
	if h.left < h.right {
		return h.left
	}
	return h.right
}

func trap(height []int) int {
	elevationSize := len(height)
	if elevationSize == 0 {
		return 0
	}
	h := make([]highest, elevationSize)
	h[0].left = height[0]
	h[elevationSize-1].right = height[elevationSize-1]
	for i := 1; i < elevationSize; i++ {
		if h[i-1].left < height[i] {
			h[i].left = height[i]
		} else {
			h[i].left = h[i-1].left
		}
		if h[elevationSize-i].right < height[elevationSize-i-1] {
			h[elevationSize-i-1].right = height[elevationSize-i-1]
		} else {
			h[elevationSize-i-1].right = h[elevationSize-i].right
		}
	}

	water := 0

	for i := 1; i < elevationSize-1; i++ {
		waterInc := h[i].min() - height[i]
		if waterInc > 0 {
			water += waterInc
		}
	}

	return water
}

func TestTrappingRainWater(t *testing.T) {
	assert.Equal(t, 6, trap([]int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}))
	assert.Equal(t, 9, trap([]int{4, 2, 0, 3, 2, 5}))
	assert.Equal(t, 0, trap([]int{}))
}
