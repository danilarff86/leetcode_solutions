package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func canCompleteCircuitN2(gas []int, cost []int) int {
	n := len(gas)

	for start := 0; start < n; start++ {
		for i, fuel := start, 0; fuel >= 0; {
			fuel += gas[i] - cost[i]
			i++
			if i == n {
				i = 0
			}
			if i == start && fuel >= 0 {
				return start
			}
		}
	}

	return -1
}

func canCompleteCircuit(gas []int, cost []int) int {
	fuel, currentFuel := 0, 0
	start := 0
	n := len(cost)

	for i := 0; i < n; i++ {
		diff := gas[i] - cost[i]
		fuel += diff
		currentFuel += diff
		if currentFuel < 0 {
			start = i + 1
			currentFuel = 0
		}
	}

	if fuel < 0 {
		return -1
	}

	return start
}

func TestCanCompleteCircuit(t *testing.T) {
	for _, tc := range []struct {
		name     string
		gas      []int
		cost     []int
		expected int
	}{
		{
			name:     "Example 1",
			gas:      []int{1, 2, 3, 4, 5},
			cost:     []int{3, 4, 5, 1, 2},
			expected: 3,
		},
		{
			name:     "Example 2",
			gas:      []int{2, 3, 4},
			cost:     []int{3, 4, 3},
			expected: -1,
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			assert.Equal(t, tc.expected, canCompleteCircuitN2(tc.gas, tc.cost))
			assert.Equal(t, tc.expected, canCompleteCircuit(tc.gas, tc.cost))
		})
	}
}
