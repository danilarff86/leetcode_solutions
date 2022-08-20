package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func minimumTotal(triangle [][]int) int {
	tLen := len(triangle)
	dp := make([][]int, tLen)
	dp[0] = make([]int, 1)
	dp[0][0] = triangle[0][0]
	for iRow := 1; iRow < tLen; iRow++ {
		dp[iRow] = make([]int, iRow+1)
		dp[iRow][0] = dp[iRow-1][0] + triangle[iRow][0]
		dp[iRow][iRow] = dp[iRow-1][iRow-1] + triangle[iRow][iRow]
		for iCol := 1; iCol < iRow; iCol++ {
			dp[iRow][iCol] = triangle[iRow][iCol] + min(dp[iRow-1][iCol-1], dp[iRow-1][iCol])
		}
	}
	res := 0xFFFFFFFF
	for _, v := range dp[tLen-1] {
		res = min(res, v)
	}
	return res
}

func TestTriangle(t *testing.T) {
	assert.Equal(t, 11, minimumTotal([][]int{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}))
	assert.Equal(t, -10, minimumTotal([][]int{{-10}}))
}
