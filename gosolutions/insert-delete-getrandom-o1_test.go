package gosolutions

import (
	"math/rand"
	"testing"

	"github.com/stretchr/testify/assert"
)

type RandomizedSet struct {
	elementsSet   map[int]int
	elementsArray []int
}

/** Initialize your data structure here. */
func RandomizedSetConstructor() RandomizedSet {
	return RandomizedSet{
		elementsSet: make(map[int]int),
	}
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
func (rs *RandomizedSet) Insert(val int) bool {
	if _, ok := rs.elementsSet[val]; ok {
		return false
	}
	rs.elementsArray = append(rs.elementsArray, val)
	rs.elementsSet[val] = len(rs.elementsArray) - 1
	return true
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
func (rs *RandomizedSet) Remove(val int) bool {
	if idx, ok := rs.elementsSet[val]; ok {
		delete(rs.elementsSet, val)
		rs.elementsArray[idx] = rs.elementsArray[len(rs.elementsArray)-1]
		rs.elementsArray = rs.elementsArray[:len(rs.elementsArray)-1]
		if idx < len(rs.elementsArray) {
			rs.elementsSet[rs.elementsArray[idx]] = idx
		}
		return true
	}
	return false
}

/** Get a random element from the set. */
func (rs *RandomizedSet) GetRandom() int {
	return rs.elementsArray[rand.Intn(len(rs.elementsArray))]
}

func TestInsertDeleteGetRandomO1(t *testing.T) {
	{
		randomizedSet := RandomizedSetConstructor()
		assert.True(t, randomizedSet.Insert(1))
		assert.False(t, randomizedSet.Remove(2))
		assert.True(t, randomizedSet.Insert(2))
		assert.Contains(t, []int{1, 2}, randomizedSet.GetRandom())
		assert.True(t, randomizedSet.Remove(1))
		assert.False(t, randomizedSet.Insert(2))
		assert.Equal(t, 2, randomizedSet.GetRandom())
	}
	{
		randomizedSet := RandomizedSetConstructor()
		assert.True(t, randomizedSet.Insert(0))
		assert.True(t, randomizedSet.Insert(1))
		assert.True(t, randomizedSet.Remove(0))
		assert.True(t, randomizedSet.Insert(2))
		assert.True(t, randomizedSet.Remove(1))
		assert.Equal(t, 2, randomizedSet.GetRandom())
	}
	{
		randomizedSet := RandomizedSetConstructor()
		assert.False(t, randomizedSet.Remove(0))
		assert.False(t, randomizedSet.Remove(0))
		assert.True(t, randomizedSet.Insert(0))
		assert.Equal(t, 0, randomizedSet.GetRandom())
		assert.True(t, randomizedSet.Remove(0))
		assert.True(t, randomizedSet.Insert(0))
	}
	{
		randomizedSet := RandomizedSetConstructor()
		assert.True(t, randomizedSet.Insert(3))
		assert.False(t, randomizedSet.Insert(3))
		assert.Equal(t, 3, randomizedSet.GetRandom())
		assert.Equal(t, 3, randomizedSet.GetRandom())
		assert.True(t, randomizedSet.Insert(1))
		assert.True(t, randomizedSet.Remove(3))
		assert.Equal(t, 1, randomizedSet.GetRandom())
		assert.Equal(t, 1, randomizedSet.GetRandom())
		assert.True(t, randomizedSet.Insert(0))
		assert.True(t, randomizedSet.Remove(0))
	}
}
