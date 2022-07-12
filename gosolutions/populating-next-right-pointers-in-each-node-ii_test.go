package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func connect2(root *Node) *Node {
	nodeQueue := []*Node{}

	nodesOnLevel := 1
	nodesOnNextLevel := 0
	nodesCnt := 0

	if root != nil {
		nodeQueue = append(nodeQueue, root)
	}

	for len(nodeQueue) > 0 {
		node := nodeQueue[0]
		nodeQueue = nodeQueue[1:]

		if node.Left != nil {
			nodeQueue = append(nodeQueue, node.Left)
			nodesOnNextLevel++
		}

		if node.Right != nil {
			nodeQueue = append(nodeQueue, node.Right)
			nodesOnNextLevel++
		}

		nodesCnt++
		if nodesCnt == nodesOnLevel {
			nodesCnt = 0
			nodesOnLevel = nodesOnNextLevel
			nodesOnNextLevel = 0
		} else {
			node.Next = nodeQueue[0]
		}
	}

	return root
}

func TestConnect2(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    string
		expected string
	}{
		{
			name:     "Example 1",
			input:    "[1,2,3,4,5,null,7]",
			expected: "[1,#,2,3,#,4,5,7,#]",
		},
		{
			name:     "Example 2",
			input:    "[]",
			expected: "[]",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			inputNode := nodeFromString(tc.input)
			actual := nodeToConnectedList(connect2(inputNode))

			assert.Equal(t, tc.expected, actual)
		})
	}
}
