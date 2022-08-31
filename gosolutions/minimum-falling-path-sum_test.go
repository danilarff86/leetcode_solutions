package gosolutions

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

func minFallingPathSum(matrix [][]int) int {
	n := len(matrix)
	if n == 1 {
		return matrix[0][0]
	}

	dp := make([][]int, n)
	dp[0] = make([]int, n)

	for j := 0; j < n; j++ {
		dp[0][j] = matrix[0][j]
	}

	for i := 1; i < n; i++ {
		dp[i] = make([]int, n)
		dp[i][0] = matrix[i][0] + min(dp[i-1][0], dp[i-1][1])
		dp[i][n-1] = matrix[i][n-1] + min(dp[i-1][n-1], dp[i-1][n-2])
		for j := 1; j < n-1; j++ {
			v := min(dp[i-1][j-1], dp[i-1][j])
			v = min(v, dp[i-1][j+1])
			dp[i][j] = matrix[i][j] + v
		}
	}

	res := math.MaxInt
	for j := 0; j < n; j++ {
		if dp[n-1][j] < res {
			res = dp[n-1][j]
		}
	}

	return res
}

func TestMinimumFallingPathSum(t *testing.T) {
	assert.Equal(t, 13, minFallingPathSum([][]int{{2, 1, 3}, {6, 5, 4}, {7, 8, 9}}))
	assert.Equal(t, -59, minFallingPathSum([][]int{{-19, 57}, {-40, -5}}))
	assert.Equal(t, 114, minFallingPathSum([][]int{{82, 81}, {69, 33}}))
}
