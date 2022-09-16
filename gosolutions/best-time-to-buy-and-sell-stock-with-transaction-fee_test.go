package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxProfitWithFee(prices []int, fee int) int {
	n := len(prices)

	type dpCell struct {
		withStock    int
		withoutStock int
	}

	dp := make([]dpCell, n+1)
	for i := n - 1; i >= 0; i-- {
		dp[i] = dpCell{
			withStock:    max(dp[i+1].withoutStock-prices[i], dp[i+1].withStock),
			withoutStock: max(dp[i+1].withStock+prices[i]-fee, dp[i+1].withoutStock),
		}
	}

	return dp[0].withStock
}

func TestBestTimeToBuyAndSellStockWithTransactionFee(t *testing.T) {
	assert.Equal(t, 8, maxProfitWithFee([]int{1, 3, 2, 8, 4, 9}, 2))
	assert.Equal(t, 6, maxProfitWithFee([]int{1, 3, 7, 5, 10, 3}, 3))
}
