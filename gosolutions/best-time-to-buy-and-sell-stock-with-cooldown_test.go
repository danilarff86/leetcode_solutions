package gosolutions

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxProfitWithCooldownTopDown(prices []int) int {
	n := len(prices)

	memo := make([][]int, n)
	for i := 0; i < n; i++ {
		memo[i] = []int{math.MinInt, math.MinInt}
	}

	var dp func(i, holding int) int
	dp = func(i, holding int) int {
		if i >= n {
			return 0
		}
		if memo[i][holding] == math.MinInt {
			actionProfit := 0
			if holding == 1 {
				actionProfit = dp(i+2, 0) + prices[i]
			} else {
				actionProfit = dp(i+1, 1) - prices[i]
			}
			memo[i][holding] = max(actionProfit, dp(i+1, holding))
		}
		return memo[i][holding]
	}

	return dp(0, 0)
}

func maxProfitWithCooldown(prices []int) int {
	n := len(prices)

	type stateData struct {
		nonHolding int
		holding    int
	}

	dp := make([]stateData, n+2)

	for i := n - 1; i >= 0; i-- {
		dp[i] = stateData{
			nonHolding: max(dp[i+1].holding-prices[i], dp[i+1].nonHolding),
			holding:    max(dp[i+2].nonHolding+prices[i], dp[i+1].holding),
		}
	}

	return dp[0].nonHolding
}

func TestBestTimeToBuyAndSellStockWithCooldown(t *testing.T) {
	assert.Equal(t, 3, maxProfitWithCooldownTopDown([]int{1, 2, 3, 0, 2}))
	assert.Equal(t, 0, maxProfitWithCooldownTopDown([]int{1}))

	assert.Equal(t, 3, maxProfitWithCooldown([]int{1, 2, 3, 0, 2}))
	assert.Equal(t, 0, maxProfitWithCooldown([]int{1}))
}
