package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func uniquePaths(m int, n int) int {
	dp := make([]int, m)
	for i := 0; i < m; i++ {
		dp[i] = 1
	}

	for i := 1; i < n; i++ {
		for j := 1; j < m; j++ {
			dp[j] += dp[j-1]
		}
	}

	return dp[m-1]
}

func TestUniquePaths(t *testing.T) {
	assert.Equal(t, 28, uniquePaths(3, 7))
	assert.Equal(t, 3, uniquePaths(3, 2))
	assert.Equal(t, 28, uniquePaths(7, 3))
	assert.Equal(t, 6, uniquePaths(3, 3))
}

func BenchmarkUniquePaths(b *testing.B) {
	for n := 1; n < b.N; n++ {
		uniquePaths(3, 7)
	}
}
