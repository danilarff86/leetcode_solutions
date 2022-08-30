package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func change(amount int, coins []int) int {
	dp := make([]int, amount+1)
	dp[0] = 1
	for _, c := range coins {
		for i := c; i <= amount; i++ {
			dp[i] += dp[i-c]
		}
	}

	return dp[amount]
}

func TestCoinChange2(t *testing.T) {
	assert.Equal(t, 4, change(5, []int{1, 2, 5}))
	assert.Equal(t, 0, change(2, []int{3}))
	assert.Equal(t, 1, change(10, []int{10}))
}
