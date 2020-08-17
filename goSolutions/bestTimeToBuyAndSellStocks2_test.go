package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maxProfit2(prices []int) int {
	overallProfit := 0
	i := 0
	lastIndex := len(prices) - 1
	for i < lastIndex {
		for i < lastIndex && prices[i] >= prices[i+1] {
			i++
		}
		lowest := prices[i]
		for i < lastIndex && prices[i] <= prices[i+1] {
			i++
		}
		highest := prices[i]
		profit := highest - lowest
		overallProfit += profit
	}

	return overallProfit
}

func TestBestTimeToBuyAndSellStock2(t *testing.T) {
	assert.Equal(t, 7, maxProfit2([]int{7, 1, 5, 3, 6, 4}))
	assert.Equal(t, 4, maxProfit2([]int{1, 2, 3, 4, 5}))
	assert.Equal(t, 0, maxProfit2([]int{7, 6, 4, 3, 1}))
}
