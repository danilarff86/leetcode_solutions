package gosolutions

import (
	"container/heap"
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

type EdgeInfo struct {
	distance   int
	targetNode int
}

type EdgeHeap []EdgeInfo

func (h EdgeHeap) Len() int {
	return len(h)
}

func (h EdgeHeap) Less(i, j int) bool {
	return h[i].distance < h[j].distance
}

func (h EdgeHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

func (h *EdgeHeap) Push(x interface{}) {
	*h = append(*h, x.(EdgeInfo))
}

func (h *EdgeHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func networkDelayTime(times [][]int, n int, k int) int {
	edgeList := make([][]EdgeInfo, n)

	for _, edge := range times {
		edgeList[edge[0]-1] = append(edgeList[edge[0]-1], EdgeInfo{
			targetNode: edge[1] - 1,
			distance:   edge[2],
		})
	}

	visited := make([]bool, n)
	distances := make([]int, n)
	for i := 0; i < n; i++ {
		distances[i] = math.MaxInt32
	}

	h := EdgeHeap{}
	heap.Push(&h, EdgeInfo{
		distance:   0,
		targetNode: k - 1,
	})
	distances[k-1] = 0

	for h.Len() > 0 {
		node := heap.Pop(&h).(EdgeInfo)
		for _, e := range edgeList[node.targetNode] {
			dist := e.distance + node.distance
			if dist < distances[e.targetNode] {
				distances[e.targetNode] = dist
			}
			if !visited[e.targetNode] {
				heap.Push(&h, EdgeInfo{
					distance:   dist,
					targetNode: e.targetNode,
				})
			}
		}
		visited[node.targetNode] = true
	}

	res := 0
	for _, dist := range distances {
		if dist == math.MaxInt32 {
			return -1
		}
		if dist > res {
			res = dist
		}
	}

	return res
}

func TestNetworkDelayTime(t *testing.T) {
	assert.Equal(t, 2, networkDelayTime([][]int{{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2))
	assert.Equal(t, 1, networkDelayTime([][]int{{1, 2, 1}}, 2, 1))
	assert.Equal(t, -1, networkDelayTime([][]int{{1, 2, 1}}, 2, 2))
}
