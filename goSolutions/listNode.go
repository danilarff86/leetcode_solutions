package goSolutions

type ListNode struct {
	Val  int
	Next *ListNode
}

func linkedListToArray(node *ListNode) []int {
	arr := make([]int, 0)
	for node != nil {
		arr = append(arr, node.Val)
		node = node.Next
	}
	return arr
}

func linkedListFromArray(arr []int) *ListNode {
	var dummy ListNode
	last := &dummy
	for _, val := range arr {
		last.Next = &ListNode{
			Val: val,
		}
		last = last.Next
	}
	return dummy.Next
}

func linkedListLastNode(node *ListNode) *ListNode {
	if node == nil {
		return nil
	}

	for node.Next != nil {
		node = node.Next
	}

	return node
}

func linkedListAdvance(node *ListNode, skip int) *ListNode {
	if node == nil {
		return nil
	}

	for node.Next != nil && skip > 0 {
		node = node.Next
		skip--
	}

	return node
}
