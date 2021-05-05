package gosolutions

import (
	"container/heap"
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

type IntHeap []int

func (h IntHeap) Len() int {
	return len(h)
}

func (h IntHeap) Less(i, j int) bool {
	return h[i] < h[j]
}

func (h IntHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func minMeetingRooms(intervals [][]int) int {
	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0]
	})
	res := 0
	h := IntHeap{}
	for i := 0; i < len(intervals); i++ {
		start := intervals[i][0]
		for h.Len() > 0 && h[0] <= start {
			heap.Pop(&h)
		}
		heap.Push(&h, intervals[i][1])
		if h.Len() > res {
			res = h.Len()
		}
	}
	return res
}

func TestMeetingRoomsII(t *testing.T) {
	assert.Equal(t, 2, minMeetingRooms([][]int{{0, 30}, {5, 10}, {15, 20}}))
	assert.Equal(t, 1, minMeetingRooms([][]int{{7, 10}, {2, 4}}))
	assert.Equal(t, 2, minMeetingRooms([][]int{{9, 10}, {4, 9}, {4, 17}}))
	assert.Equal(t, 2, minMeetingRooms([][]int{{2, 11}, {6, 16}, {11, 16}}))
}

func BenchmarkMeetingRoomsII(b *testing.B) {
	for n := 0; n < b.N; n++ {
		minMeetingRooms([][]int{{0, 30}, {5, 10}, {15, 20}})
	}
}
