package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func minCostClimbingStairs(cost []int) int {
	for i := 2; i < len(cost); i++ {
		cost[i] = min(cost[i-1], cost[i-2]) + cost[i]
	}
	return min(cost[len(cost)-1], cost[len(cost)-2])
}

func TestMinCostClimbingStairs(t *testing.T) {
	assert.Equal(t, 15, minCostClimbingStairs([]int{10, 15, 20}))
	assert.Equal(t, 6, minCostClimbingStairs([]int{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}))
}
