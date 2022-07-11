package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func pruneTree(root *TreeNode) *TreeNode {
	if isSatisfied(root) {
		return root
	}
	return nil
}

func isSatisfied(node *TreeNode) bool {
	if node == nil {
		return false
	}

	if !isSatisfied(node.Left) {
		node.Left = nil
	}

	if !isSatisfied(node.Right) {
		node.Right = nil
	}

	return node.Val != 0 || node.Left != nil || node.Right != nil
}

func TestPruneTree(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    string
		expected string
	}{
		{
			name:     "Example 1",
			input:    "[1,null,0,0,1]",
			expected: "[1,null,0,null,1]",
		},
		{
			name:     "Example 2",
			input:    "[1,0,1,0,0,0,1]",
			expected: "[1,null,1,null,1]",
		},
		{
			name:     "Example 3",
			input:    "[1,1,0,1,1,0,1,0]",
			expected: "[1,1,0,1,1,null,1]",
		},
		{
			name:     "Example 4",
			input:    "[0,null,0,0,0]",
			expected: "[]",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			inputNode := treeNodeFromString(tc.input)
			expectedNode := treeNodeFromString(tc.expected)
			outputNode := pruneTree(inputNode)

			assert.Equal(t, expectedNode, outputNode)
		})
	}
}
