package gosolutions

import (
	"math"
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

func coinChangeTopDown(coins []int, amount int) int {
	var dp func(i, amount int) int
	dp = func(i, amount int) int {
		if amount == 0 {
			return i
		} else if amount < 0 {
			return math.MaxInt
		}

		res := math.MaxInt
		for _, c := range coins {
			res = min(res, dp(i+1, amount-c))
		}

		return res
	}

	r := dp(0, amount)

	if r == math.MaxInt {
		return -1
	}

	return r
}

func coinChangeNew(coins []int, amount int) int {
	dp := make([]int, amount+1)
	for i := 1; i <= amount; i++ {
		dp[i] = math.MaxInt
		for _, c := range coins {
			if i >= c && (dp[i-c] != math.MaxInt) && (dp[i-c]+1 < dp[i]) {
				dp[i] = dp[i-c] + 1
			}
		}
	}
	if dp[amount] == math.MaxInt {
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

	assert.Equal(t, 3, coinChangeTopDown([]int{1, 2, 5}, 11))
	assert.Equal(t, -1, coinChangeTopDown([]int{2}, 3))
	assert.Equal(t, 0, coinChangeTopDown([]int{1}, 0))
	assert.Equal(t, 1, coinChangeTopDown([]int{1}, 1))
	assert.Equal(t, 2, coinChangeTopDown([]int{1}, 2))

	assert.Equal(t, 3, coinChangeNew([]int{1, 2, 5}, 11))
	assert.Equal(t, -1, coinChangeNew([]int{2}, 3))
	assert.Equal(t, 0, coinChangeNew([]int{1}, 0))
	assert.Equal(t, 1, coinChangeNew([]int{1}, 1))
	assert.Equal(t, 2, coinChangeNew([]int{1}, 2))
}
