package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxProfit(prices []int) int {
	minVal := int(^uint(0) >> 1)
	maxProfit := 0
	for _, val := range prices {
		profit := val - minVal
		if profit > maxProfit {
			maxProfit = profit
		} else if val < minVal {
			minVal = val
		}
	}
	return maxProfit
}

func TestBestTimeToBuyAndSellStock(t *testing.T) {
	assert.Equal(t, 5, maxProfit([]int{7, 1, 5, 3, 6, 4}))
	assert.Equal(t, 0, maxProfit([]int{7, 6, 4, 3, 1}))
}
