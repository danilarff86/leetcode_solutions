package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func getRow(rowIndex int) []int {
	prev := make([]int, rowIndex+1)
	row := make([]int, rowIndex+1)
	row[0] = 1
	for i := 1; i < rowIndex+1; i++ {
		row, prev = prev, row
		row[0] = 1
		row[i] = 1
		for j := 1; j < i; j++ {
			row[j] = prev[j-1] + prev[j]
		}
	}

	return row
}

func TestPascalTriangle2(t *testing.T) {
	assert.Equal(t, []int{1, 3, 3, 1}, getRow(3))
	assert.Equal(t, []int{1}, getRow(0))
	assert.Equal(t, []int{1, 1}, getRow(1))
}
