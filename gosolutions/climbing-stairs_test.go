package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func climbStairs(n int) int {
	prev1 := 0
	prev2 := 1
	current := 0
	for i := 0; i < n; i++ {
		current = prev1 + prev2
		prev1 = prev2
		prev2 = current
	}
	return current
}

func TestClimbingStairs(t *testing.T) {
	assert.Equal(t, 2, climbStairs(2))
	assert.Equal(t, 3, climbStairs(3))
}
