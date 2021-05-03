package gosolutions

import (
	"fmt"
)

// TreeNode is definition of node in binary tree
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func treeNodeListToStringList(nodes []*TreeNode) []string {
	var res []string
	for _, n := range nodes {
		res = append(res, treeNodeToString(n))
	}
	return res
}

func treeNodeToString(root *TreeNode) string {
	if root == nil {
		return "[]"
	}

	var output string
	q := []*TreeNode{root}
	for len(q) > 0 {
		node := q[0]
		q = q[1:]

		if node == nil {
			output += "null, "
			continue
		}

		output += fmt.Sprintf("%d, ", node.Val)
		q = append(q, node.Left, node.Right)
	}
	return "[" + output[:len(output)-2] + "]"
}
