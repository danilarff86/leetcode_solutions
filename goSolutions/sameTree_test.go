package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func isSameTree(p *TreeNode, q *TreeNode) bool {
	if p == nil {
		if q != nil {
			return false
		}
		return true
	}

	pQueue := []*TreeNode{p}
	qQueue := []*TreeNode{q}

	for len(pQueue) > 0 {
		p := pQueue[0]
		pQueue = pQueue[1:]
		q := qQueue[0]
		qQueue = qQueue[1:]

		if p != nil {
			if q == nil || p.Val != q.Val {
				return false
			}

			pQueue = append(pQueue, p.Left)
			pQueue = append(pQueue, p.Right)
			qQueue = append(qQueue, q.Left)
			qQueue = append(qQueue, q.Right)
		} else if q != nil {
			return false
		}
	}

	return len(pQueue) == len(qQueue)
}

func TestSameTree(t *testing.T) {
	{
		node := &TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 2,
			},
			Right: &TreeNode{
				Val: 3,
			},
		}

		assert.True(t, isSameTree(node, node))
	}
	{
		p := &TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 2,
			},
			Right: &TreeNode{
				Val: 1,
			},
		}
		q := &TreeNode{
			Val: 1,
			Left: &TreeNode{
				Val: 1,
			},
			Right: &TreeNode{
				Val: 2,
			},
		}

		assert.False(t, isSameTree(p, q))
	}
	{
		p := &TreeNode{
			Val: 1,
		}
		var q *TreeNode = nil

		assert.False(t, isSameTree(p, q))
	}
}
