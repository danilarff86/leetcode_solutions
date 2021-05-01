package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func getIntersectionNode(headA, headB *ListNode) *ListNode {
	if headA == nil || headB == nil {
		return nil
	}

	nodeA := headA
	nodeB := headB
	var lastA *ListNode
	var lastB *ListNode
	for {
		if nodeA == nodeB {
			return nodeA
		}

		if nodeA.Next == nil {
			lastA = nodeA
			nodeA = headB
			if lastB != nil && lastB != lastA {
				return nil
			}
		} else {
			nodeA = nodeA.Next
		}

		if nodeB.Next == nil {
			lastB = nodeB
			nodeB = headA
			if lastA != nil && lastA != lastB {
				return nil
			}
		} else {
			nodeB = nodeB.Next
		}
	}
}

func TestIntersectionOfTwoLinkedLists(t *testing.T) {
	{
		headA := linkedListFromArray([]int{4, 1, 8, 4, 5})
		headB := linkedListFromArray([]int{5, 6, 1})
		expected := linkedListAdvance(headA, 2)
		linkedListLastNode(headB).Next = expected
		assert.Equal(t, expected, getIntersectionNode(headA, headB))
	}
	{
		headA := linkedListFromArray([]int{1, 9, 1, 2, 4})
		headB := linkedListFromArray([]int{3})
		expected := linkedListAdvance(headA, 3)
		linkedListLastNode(headB).Next = expected
		assert.Equal(t, expected, getIntersectionNode(headA, headB))
	}
	{
		headA := linkedListFromArray([]int{2, 6, 4})
		headB := linkedListFromArray([]int{1, 5})
		assert.Nil(t, getIntersectionNode(headA, headB))
	}
	{
		headA := linkedListFromArray([]int{1})
		headB := headA
		expected := headA
		assert.Equal(t, expected, getIntersectionNode(headA, headB))
	}
	{
		headA := linkedListFromArray([]int{1})
		var headB *ListNode
		assert.Nil(t, getIntersectionNode(headA, headB))
	}
}
