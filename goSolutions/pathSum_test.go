package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func hasPathSum(root *TreeNode, sum int) bool {
	if root == nil {
		return false
	}

	type NodeContext struct {
		node *TreeNode
		sum  int
	}

	queue := []*NodeContext{{root, 0}}
	for len(queue) > 0 {
		item := queue[0]
		queue = queue[1:]

		actualSum := item.sum + item.node.Val

		leafNode := true
		if item.node.Left != nil {
			queue = append(queue, &NodeContext{item.node.Left, actualSum})
			leafNode = false
		}
		if item.node.Right != nil {
			queue = append(queue, &NodeContext{item.node.Right, actualSum})
			leafNode = false
		}

		if leafNode && actualSum == sum {
			return true
		}
	}

	return false
}

func TestPathSum(t *testing.T) {
	{
		node := &TreeNode{
			Val: 5,
			Left: &TreeNode{
				Val: 4,
				Left: &TreeNode{
					Val: 11,
					Left: &TreeNode{
						Val: 7,
					},
					Right: &TreeNode{
						Val: 2,
					},
				},
			},
			Right: &TreeNode{
				Val: 8,
				Left: &TreeNode{
					Val: 13,
				},
				Right: &TreeNode{
					Val: 4,
					Right: &TreeNode{
						Val: 1,
					},
				},
			},
		}

		assert.True(t, hasPathSum(node, 22))
	}
	{
		assert.False(t, hasPathSum(nil, 1))
	}
	{
		node := &TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 2,
			},
		}

		assert.False(t, hasPathSum(node, 1))
	}
}
