package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func maximalSquare(matrix [][]byte) int {
	m := len(matrix)
	n := len(matrix[0])
	dp := make([][]int, m+1)
	for i := 0; i < len(dp); i++ {
		dp[i] = make([]int, n+1)
	}

	res := 0

	for i := m - 1; i >= 0; i-- {
		for j := n - 1; j >= 0; j-- {
			if matrix[i][j] == '1' {
				dp[i][j] = 1 + min(min(dp[i+1][j], dp[i][j+1]), dp[i+1][j+1])
				res = max(res, dp[i][j])
			}
		}
	}

	return res * res
}

func TestMaximalSquare(t *testing.T) {
	assert.Equal(t, 4, maximalSquare([][]byte{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}))
	assert.Equal(t, 1, maximalSquare([][]byte{{'0', '1'}, {'1', '0'}}))
	assert.Equal(t, 0, maximalSquare([][]byte{{'0'}}))
}
