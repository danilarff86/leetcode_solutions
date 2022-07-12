package gosolutions

import (
	"strconv"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

func connect(root *Node) *Node {
	nodeQueue := []*Node{}

	nodesOnLevel := 1
	nodesCnt := 0

	if root != nil {
		nodeQueue = append(nodeQueue, root)
	}

	for len(nodeQueue) > 0 {
		node := nodeQueue[0]
		nodeQueue = nodeQueue[1:]

		if node.Left != nil {
			nodeQueue = append(nodeQueue, node.Left)
		}

		if node.Right != nil {
			nodeQueue = append(nodeQueue, node.Right)
		}

		nodesCnt++
		if nodesCnt == nodesOnLevel {
			nodesCnt = 0
			nodesOnLevel *= 2
		} else {
			node.Next = nodeQueue[0]
		}
	}

	return root
}

func TestConnect(t *testing.T) {
	for _, tc := range []struct {
		name     string
		input    string
		expected string
	}{
		{
			name:     "Example 1",
			input:    "[1,2,3,4,5,6,7]",
			expected: "[1,#,2,3,#,4,5,6,7,#]",
		},
		{
			name:     "Example 2",
			input:    "[]",
			expected: "[]",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			inputNode := nodeFromString(tc.input)
			actual := nodeToConnectedList(connect(inputNode))

			assert.Equal(t, tc.expected, actual)
		})
	}
}

func nodeToConnectedList(node *Node) string {
	if node == nil {
		return "[]"
	}

	nodeQueue := []*Node{node}
	var nodes []string

	for len(nodeQueue) > 0 {
		node := nodeQueue[0]
		nodeQueue = nodeQueue[1:]

		nodes = append(nodes, strconv.Itoa(node.Val))
		if node.Next == nil {
			nodes = append(nodes, "#")
		}

		if node.Left != nil {
			nodeQueue = append(nodeQueue, node.Left)
		}

		if node.Right != nil {
			nodeQueue = append(nodeQueue, node.Right)
		}
	}

	return "[" + strings.Join(nodes, ",") + "]"
}
