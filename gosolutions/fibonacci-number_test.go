package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func fib(n int) int {
	if n == 0 {
		return 0
	}
	if n == 1 {
		return 1
	}

	n1 := 0
	n2 := 1

	for i := 2; i <= n; i++ {
		n1 += n2
		n1, n2 = n2, n1
	}

	return n2
}

func TestFibonacciNumber(t *testing.T) {
	assert.Equal(t, 1, fib(2))
	assert.Equal(t, 2, fib(3))
	assert.Equal(t, 3, fib(4))
}
