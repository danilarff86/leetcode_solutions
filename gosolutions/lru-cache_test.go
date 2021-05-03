package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type dListNode struct {
	key  int
	prev *dListNode
	next *dListNode
}

type mapValue struct {
	val  int
	node *dListNode
}

type LRUCache struct {
	data     map[int]*mapValue
	head     *dListNode
	tail     *dListNode
	capacity int
}

func Constructor(capacity int) LRUCache {
	cache := LRUCache{
		data:     make(map[int]*mapValue),
		head:     &dListNode{key: -1},
		tail:     &dListNode{key: -1},
		capacity: capacity,
	}
	cache.head.next = cache.tail
	cache.tail.prev = cache.head
	return cache
}

func (c *LRUCache) getImpl(key int) *mapValue {
	if v, ok := c.data[key]; ok {
		v.node.prev.next = v.node.next
		v.node.next.prev = v.node.prev
		v.node.next = c.head.next
		v.node.next.prev = v.node
		v.node.prev = c.head
		c.head.next = v.node
		return v
	}
	return nil
}

func (c *LRUCache) Get(key int) int {
	if v := c.getImpl(key); v != nil {
		return v.val
	}
	return -1
}

func (c *LRUCache) Put(key int, value int) {
	if v := c.getImpl(key); v != nil {
		v.val = value
		return
	}
	if len(c.data) == c.capacity {
		delete(c.data, c.tail.prev.key)
		c.tail.prev = c.tail.prev.prev
		c.tail.prev.next = c.tail
	}
	node := &dListNode{
		key:  key,
		prev: c.head,
		next: c.head.next,
	}
	node.next.prev = node
	c.head.next = node
	c.data[key] = &mapValue{
		val:  value,
		node: node,
	}
}

func TestLRUCache(t *testing.T) {
	{
		cache := Constructor(2)
		cache.Put(1, 1)
		cache.Put(2, 2)
		assert.Equal(t, 1, cache.Get(1))
		cache.Put(3, 3)
		assert.Equal(t, -1, cache.Get(2))
		cache.Put(4, 4)
		assert.Equal(t, -1, cache.Get(1))
		assert.Equal(t, 3, cache.Get(3))
		assert.Equal(t, 4, cache.Get(4))
	}
	{
		cache := Constructor(2)
		assert.Equal(t, -1, cache.Get(2))
		cache.Put(2, 6)
		assert.Equal(t, -1, cache.Get(1))
		cache.Put(1, 5)
		cache.Put(1, 2)
		assert.Equal(t, 2, cache.Get(1))
		assert.Equal(t, 6, cache.Get(2))
	}
}
