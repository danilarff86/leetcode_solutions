package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func minCostClimbingStairs(cost []int) int {
	oneBefore, twoBefore := cost[1], cost[0]
	for i := 2; i < len(cost); i++ {
		tmp := oneBefore
		oneBefore = min(oneBefore, twoBefore) + cost[i]
		twoBefore = tmp
	}
	return min(oneBefore, twoBefore)
}

func minCostClimbingStairsReuse(cost []int) int {
	for i := 2; i < len(cost); i++ {
		cost[i] = min(cost[i-1], cost[i-2]) + cost[i]
	}
	return min(cost[len(cost)-1], cost[len(cost)-2])
}

func TestMinCostClimbingStairs(t *testing.T) {
	assert.Equal(t, 15, minCostClimbingStairsReuse([]int{10, 15, 20}))
	assert.Equal(t, 6, minCostClimbingStairsReuse([]int{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}))

	assert.Equal(t, 15, minCostClimbingStairs([]int{10, 15, 20}))
	assert.Equal(t, 6, minCostClimbingStairs([]int{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}))
}
