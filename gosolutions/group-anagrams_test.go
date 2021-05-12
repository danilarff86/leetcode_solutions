package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func groupAnagrams(strs []string) [][]string {
	hashes := make(map[string]int)
	var groups [][]string
	for _, s := range strs {
		h := make([]rune, 26)
		for _, c := range s {
			h[int(c)-int('a')]++
		}
		index, ok := hashes[string(h)]
		if !ok {
			groups = append(groups, []string{s})
			hashes[string(h)] = len(groups) - 1
		} else {
			groups[index] = append(groups[index], s)
		}
	}
	return groups
}

func TestGroupAnagrams(t *testing.T) {
	assert.Equal(t,
		[][]string{{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}},
		groupAnagrams([]string{"eat", "tea", "tan", "ate", "nat", "bat"}))
	assert.Equal(t, [][]string{{""}}, groupAnagrams([]string{""}))
	assert.Equal(t, [][]string{{"a"}}, groupAnagrams([]string{"a"}))
}

func BenchmarkGroupAnagrams(b *testing.B) {
	for n := 0; n < b.N; n++ {
		groupAnagrams([]string{"eat", "tea", "tan", "ate", "nat", "bat"})
	}
}
