package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func minPathSum(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])

	for j := 1; j < n; j++ {
		grid[0][j] += grid[0][j-1]
	}

	for i := 1; i < m; i++ {
		grid[i][0] += grid[i-1][0]
		for j := 1; j < n; j++ {
			grid[i][j] += min(grid[i-1][j], grid[i][j-1])
		}
	}

	return grid[m-1][n-1]
}

func TestMinimumPathSum(t *testing.T) {
	assert.Equal(t, 7, minPathSum([][]int{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}))
	assert.Equal(t, 12, minPathSum([][]int{{1, 2, 3}, {4, 5, 6}}))
}
