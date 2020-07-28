package goSolutions

import (
	"testing"

	"github.com/stretchr/testify/require"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

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

func TestSameTreeBasic1(t *testing.T) {
	node := &TreeNode{
		Val: 1,
		Left: &TreeNode{
			Val: 2,
		},
		Right: &TreeNode{
			Val: 3,
		},
	}

	require.True(t, isSameTree(node, node))
}

func TestSameTreeCase4(t *testing.T) {
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

	require.False(t, isSameTree(p, q))
}

func TestSameTreeCase5(t *testing.T) {
	p := &TreeNode{
		Val: 1,
	}
	var q *TreeNode = nil

	require.False(t, isSameTree(p, q))
}
