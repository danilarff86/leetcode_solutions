package gosolutions

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxProfit4TopDown(k int, prices []int) int {
	n := len(prices)
	memo := make([][][]int, n)
	for i := 0; i < n; i++ {
		memo[i] = make([][]int, k)
		for j := 0; j < k; j++ {
			memo[i][j] = []int{math.MinInt, math.MinInt}
		}
	}

	var dp func(i, remaining, holding int) int
	dp = func(i, remaining, holding int) int {
		if i >= n || remaining == 0 {
			return 0
		}
		if memo[i][remaining-1][holding] == math.MinInt {
			actionProfit := 0
			if holding == 1 {
				actionProfit = dp(i+1, remaining-1, 0) + prices[i]
			} else {
				actionProfit = dp(i+1, remaining, 1) - prices[i]
			}
			memo[i][remaining-1][holding] = max(actionProfit, dp(i+1, remaining, holding))
		}
		return memo[i][remaining-1][holding]
	}

	return dp(0, k, 0)
}

func maxProfit4(k int, prices []int) int {
	n := len(prices)

	dp := make([][][]int, n+1)
	dp[n] = make([][]int, k+1)
	for i := 0; i <= k; i++ {
		dp[n][i] = make([]int, 2)
	}
	for i := n - 1; i >= 0; i-- {
		dp[i] = make([][]int, k+1)
		dp[i][0] = make([]int, 2)
		for remaining := 1; remaining <= k; remaining++ {
			dp[i][remaining] = []int{
				max(dp[i+1][remaining][1]-prices[i], dp[i+1][remaining][0]),
				max(dp[i+1][remaining-1][0]+prices[i], dp[i+1][remaining][1]),
			}
		}
	}

	return dp[0][k][0]
}

func TestBestTimeToBuyAndSellStockIV(t *testing.T) {
	assert.Equal(t, 2, maxProfit4TopDown(2, []int{2, 4, 1}))
	assert.Equal(t, 7, maxProfit4TopDown(2, []int{3, 2, 6, 5, 0, 3}))
	assert.Equal(t, 3, maxProfit4TopDown(2, []int{1, 2, 4}))

	assert.Equal(t, 2, maxProfit4(2, []int{2, 4, 1}))
	assert.Equal(t, 7, maxProfit4(2, []int{3, 2, 6, 5, 0, 3}))
	assert.Equal(t, 3, maxProfit4(2, []int{1, 2, 4}))
}
