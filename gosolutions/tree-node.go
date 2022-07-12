package gosolutions

import (
	"fmt"
	"strconv"
	"strings"
)

// TreeNode is definition of node in binary tree
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

//Definition for a Node.
type Node struct {
	Val   int
	Left  *Node
	Right *Node
	Next  *Node
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

func treeNodeFromString(treeStr string) *TreeNode {
	treeStr = strings.Trim(treeStr, " ")
	treeStr = treeStr[1 : len(treeStr)-1]

	nodes := strings.Split(treeStr, ",")

	if len(nodes) == 0 || nodes[0] == "" || nodes[0] == "null" {
		return nil
	}

	val, err := strconv.ParseInt(nodes[0], 10, 32)
	if err != nil {
		panic(err)
	}
	root := &TreeNode{
		Val: int(val),
	}
	nodes = nodes[1:]

	nodeQueue := make([]*TreeNode, 0, len(nodes))
	nodeQueue = append(nodeQueue, root)

	for len(nodes) > 0 {
		item := strings.Trim(nodes[0], "")
		nodes = nodes[1:]

		node := nodeQueue[0]
		nodeQueue = nodeQueue[1:]

		if item != "null" {
			val, err := strconv.ParseInt(item, 10, 32)
			if err != nil {
				panic(err)
			}
			node.Left = &TreeNode{
				Val: int(val),
			}
			nodeQueue = append(nodeQueue, node.Left)
		}

		if len(nodes) == 0 {
			break
		}

		item = strings.Trim(nodes[0], "")
		nodes = nodes[1:]

		if item != "null" {
			val, err := strconv.ParseInt(item, 10, 32)
			if err != nil {
				panic(err)
			}
			node.Right = &TreeNode{
				Val: int(val),
			}
			nodeQueue = append(nodeQueue, node.Right)
		}
	}

	return root
}

func nodeFromString(treeStr string) *Node {
	treeStr = strings.Trim(treeStr, " ")
	treeStr = treeStr[1 : len(treeStr)-1]

	nodes := strings.Split(treeStr, ",")

	if len(nodes) == 0 || nodes[0] == "" || nodes[0] == "null" {
		return nil
	}

	val, err := strconv.ParseInt(nodes[0], 10, 32)
	if err != nil {
		panic(err)
	}
	root := &Node{
		Val: int(val),
	}
	nodes = nodes[1:]

	nodeQueue := make([]*Node, 0, len(nodes))
	nodeQueue = append(nodeQueue, root)

	for len(nodes) > 0 {
		item := strings.Trim(nodes[0], "")
		nodes = nodes[1:]

		node := nodeQueue[0]
		nodeQueue = nodeQueue[1:]

		if item != "null" {
			val, err := strconv.ParseInt(item, 10, 32)
			if err != nil {
				panic(err)
			}
			node.Left = &Node{
				Val: int(val),
			}
			nodeQueue = append(nodeQueue, node.Left)
		}

		if len(nodes) == 0 {
			break
		}

		item = strings.Trim(nodes[0], "")
		nodes = nodes[1:]

		if item != "null" {
			val, err := strconv.ParseInt(item, 10, 32)
			if err != nil {
				panic(err)
			}
			node.Right = &Node{
				Val: int(val),
			}
			nodeQueue = append(nodeQueue, node.Right)
		}
	}

	return root
}
