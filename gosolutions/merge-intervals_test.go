package gosolutions

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func mergeIntervals(intervals [][]int) [][]int {
	if len(intervals) == 0 {
		return [][]int{}
	}

	sort.Slice(intervals, func(i, j int) bool { return intervals[i][0] < intervals[j][0] })
	result := [][]int{intervals[0]}
	for i := 1; i < len(intervals); i++ {
		if intervals[i][0] <= result[len(result)-1][1] {
			if intervals[i][1] > result[len(result)-1][1] {
				result[len(result)-1][1] = intervals[i][1]
			}
		} else {
			result = append(result, intervals[i])
		}
	}

	return result
}

func mergeIntervalsOptimized(intervals [][]int) [][]int {
	lenIntervals := len(intervals)
	if lenIntervals == 0 {
		return [][]int{}
	}

	sort.Slice(intervals, func(i, j int) bool { return intervals[i][0] < intervals[j][0] })
	result := make([][]int, lenIntervals)
	result[0] = intervals[0]
	resultCount := 1
	for i := 1; i < lenIntervals; i++ {
		lastIntervalEnd := &(result[resultCount-1][1])
		interval := &(intervals[i])
		if (*interval)[0] <= *lastIntervalEnd {
			if (*interval)[1] > *lastIntervalEnd {
				*lastIntervalEnd = (*interval)[1]
			}
		} else {
			result[resultCount] = *interval
			resultCount++
		}
	}

	return result[:resultCount]
}

func TestMergeIntervals(t *testing.T) {
	assert.Equal(t, [][]int{{1, 6}, {8, 10}, {15, 18}}, mergeIntervals([][]int{{1, 3}, {2, 6}, {8, 10}, {15, 18}}))
	assert.Equal(t, [][]int{{1, 5}}, mergeIntervals([][]int{{1, 4}, {4, 5}}))
}

func BenchmarkMergeIntervals(b *testing.B) {
	for n := 0; n < b.N; n++ {
		mergeIntervalsOptimized([][]int{{1, 3}, {2, 6}, {8, 10}, {15, 18}})
	}
}
