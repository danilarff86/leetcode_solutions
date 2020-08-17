package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func generate(numRows int) [][]int {
	res := make([][]int, numRows)
	for i := range res {
		res[i] = make([]int, i+1)
		res[i][0] = 1
		res[i][i] = 1
	}

	for i := 1; i < numRows; i++ {
		currentRow := res[i]
		for j := 1; j < i; j++ {
			currentRow[j] = res[i-1][j-1] + res[i-1][j]
		}
	}
	return res
}

func TestPascalTriangle(t *testing.T) {
	assert.Equal(t, [][]int{{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}}, generate(5))
}
