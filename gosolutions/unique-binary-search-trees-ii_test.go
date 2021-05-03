package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func generateTreesImpl(start, end int) []*TreeNode {
	if start > end {
		return []*TreeNode{nil}
	}

	list := []*TreeNode{}
	for i := start; i <= end; i++ {
		left := generateTreesImpl(start, i-1)
		right := generateTreesImpl(i+1, end)
		for _, l := range left {
			for _, r := range right {
				list = append(list, &TreeNode{
					Val:   i,
					Left:  l,
					Right: r,
				})
			}
		}
	}
	return list
}

func generateTrees(n int) []*TreeNode {
	if n == 0 {
		return []*TreeNode{}
	}
	return generateTreesImpl(1, n)
}

func TestUniqueBinarySearchTreesII(t *testing.T) {
	res := generateTrees(3)
	assert.Len(t, res, 5)
	assert.Subset(t, treeNodeListToStringList(res), treeNodeListToStringList([]*TreeNode{
		{
			Val: 1,
			Right: &TreeNode{
				Val: 3,
				Left: &TreeNode{
					Val: 2,
				},
			},
		},
		{
			Val: 1,
			Right: &TreeNode{
				Val: 2,
				Right: &TreeNode{
					Val: 3,
				},
			},
		},
		{
			Val: 2,
			Left: &TreeNode{
				Val: 1,
			},
			Right: &TreeNode{
				Val: 3,
			},
		},
		{
			Val: 3,
			Left: &TreeNode{
				Val: 2,
				Left: &TreeNode{
					Val: 1,
				},
			},
		},
		{
			Val: 3,
			Left: &TreeNode{
				Val: 1,
				Right: &TreeNode{
					Val: 2,
				},
			},
		},
	}))
}
