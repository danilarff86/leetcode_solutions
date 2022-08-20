package gosolutions

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

func minDifficultyTopDown(jobDifficulty []int, d int) int {
	n := len(jobDifficulty)
	if n < d {
		return -1
	}

	memo := make([][]int, n)
	for i := 0; i < n; i++ {
		memo[i] = make([]int, d)
		for j := 0; j < d; j++ {
			memo[i][j] = math.MaxInt
		}
	}

	var dp func(i, j int) int
	dp = func(i, j int) int {
		if memo[i][j] == math.MaxInt {
			if j+1 == d {
				memo[i][j] = 0
				for k := i; k < n; k++ {
					memo[i][j] = max(memo[i][j], jobDifficulty[k])
				}
			} else {
				m := 0
				for k := i; k < n-(d-j-1); k++ {
					m = max(m, jobDifficulty[k])
					memo[i][j] = min(memo[i][j], m+dp(k+1, j+1))
				}
			}
		}

		return memo[i][j]
	}

	return dp(0, 0)
}

func minDifficulty(jobDifficulty []int, d int) int {
	n := len(jobDifficulty)
	if n < d {
		return -1
	}

	maxPerDay := n - d + 1

	dp := make([][]int, d)
	for i := 0; i < d; i++ {
		dp[i] = make([]int, maxPerDay)
	}

	dp[d-1][maxPerDay-1] = jobDifficulty[n-1]
	for i := maxPerDay - 2; i >= 0; i-- {
		dp[d-1][i] = max(dp[d-1][i+1], jobDifficulty[i+d-1])
	}

	for i := d - 2; i >= 0; i-- {
		for j := maxPerDay - 1; j >= 0; j-- {
			dp[i][j] = math.MaxInt
			m := 0
			for k := j; k < maxPerDay; k++ {
				m = max(m, jobDifficulty[i+k])
				dp[i][j] = min(dp[i][j], m+dp[i+1][k])
			}
		}
	}

	return dp[0][0]
}

func TestMinimumDifficultyOfAJobSchedule(t *testing.T) {
	assert.Equal(t, 7, minDifficultyTopDown([]int{6, 5, 4, 3, 2, 1}, 2))
	assert.Equal(t, -1, minDifficultyTopDown([]int{9, 9, 9}, 4))
	assert.Equal(t, 3, minDifficultyTopDown([]int{1, 1, 1}, 3))
	assert.Equal(t, 843, minDifficultyTopDown([]int{11, 111, 22, 222, 33, 333, 44, 444}, 6))
	assert.Equal(t, 444, minDifficultyTopDown([]int{333, 44, 444}, 1))
	assert.Equal(t, 15, minDifficultyTopDown([]int{7, 1, 7, 1, 7, 1}, 3))
	assert.Equal(t, 8, minDifficultyTopDown([]int{7, 1, 7, 1}, 2))
	assert.Equal(t, 1803, minDifficultyTopDown([]int{186, 398, 479, 206, 885, 423, 805, 112, 925, 656, 16, 932, 740, 292, 671, 360}, 4))
	assert.Equal(t, 1617, minDifficultyTopDown([]int{398, 479, 206, 885, 423, 805, 112, 925, 656, 16, 932, 740, 292, 671, 360}, 3))

	assert.Equal(t, 7, minDifficulty([]int{6, 5, 4, 3, 2, 1}, 2))
	assert.Equal(t, -1, minDifficulty([]int{9, 9, 9}, 4))
	assert.Equal(t, 3, minDifficulty([]int{1, 1, 1}, 3))
	assert.Equal(t, 843, minDifficulty([]int{11, 111, 22, 222, 33, 333, 44, 444}, 6))
	assert.Equal(t, 444, minDifficulty([]int{333, 44, 444}, 1))
	assert.Equal(t, 8, minDifficulty([]int{7, 1, 7, 1}, 2))
	assert.Equal(t, 15, minDifficulty([]int{7, 1, 7, 1, 7, 1}, 3))
	assert.Equal(t, 1803, minDifficulty([]int{186, 398, 479, 206, 885, 423, 805, 112, 925, 656, 16, 932, 740, 292, 671, 360}, 4))
	assert.Equal(t, 1617, minDifficulty([]int{398, 479, 206, 885, 423, 805, 112, 925, 656, 16, 932, 740, 292, 671, 360}, 3))
}
