package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func coinChange(coins []int, amount int) int {
	const maxVal = 0xFFFFFFFF

	dp := make([]int, amount+1)
	for i := 1; i <= amount; i++ {
		dp[i] = maxVal
		for _, coin := range coins {
			if coin <= i {
				coins := dp[i-coin] + 1
				if coins < dp[i] {
					dp[i] = coins
				}
			}
		}
	}

	if dp[amount] == maxVal {
		return -1
	}

	return dp[amount]
}

func TestCoinChange(t *testing.T) {
	assert.Equal(t, 3, coinChange([]int{1, 2, 5}, 11))
	assert.Equal(t, -1, coinChange([]int{2}, 3))
	assert.Equal(t, 0, coinChange([]int{1}, 0))
	assert.Equal(t, 1, coinChange([]int{1}, 1))
	assert.Equal(t, 2, coinChange([]int{1}, 2))
}
