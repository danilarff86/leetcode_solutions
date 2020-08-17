package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func mySqrt(x int) int {
	count := x + 1
	first := 0
	for count > 1 {
		step := count / 2
		it := first + step
		if it*it > x {
			count = step
		} else {
			first = it
			count -= step
		}
	}
	return first
}

func TestMySqrt(t *testing.T) {
	assert.Equal(t, 2, mySqrt(4))
	assert.Equal(t, 2, mySqrt(8))
	assert.Equal(t, 3, mySqrt(9))
}
