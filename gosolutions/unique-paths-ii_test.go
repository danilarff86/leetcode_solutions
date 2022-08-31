package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
	m := len(obstacleGrid)
	n := len(obstacleGrid[0])
	dp := make([]int, n)
	for i := 0; i < n; i++ {
		if obstacleGrid[0][i] != 0 {
			break
		}
		dp[i] = 1
	}

	for i := 1; i < m; i++ {
		if obstacleGrid[i][0] == 1 {
			dp[0] = 0
		}
		for j := 1; j < n; j++ {
			if obstacleGrid[i][j] == 0 {
				dp[j] += dp[j-1]
			} else {
				dp[j] = 0
			}
		}
	}

	return dp[n-1]
}

func TestUniquePathsWithObstacles(t *testing.T) {
	assert.Equal(t, 2, uniquePathsWithObstacles([][]int{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}))
	assert.Equal(t, 1, uniquePathsWithObstacles([][]int{{0, 1}, {0, 0}}))
	assert.Equal(t, 0, uniquePathsWithObstacles([][]int{{1, 0}}))
	assert.Equal(t, 0, uniquePathsWithObstacles([][]int{{0}, {1}}))
}
