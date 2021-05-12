package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type wordSearch struct {
	board [][]byte
	word  string
}

func (ws *wordSearch) exist(x, y, pos int) bool {
	if pos == len(ws.word) {
		return true
	}
	c := ws.board[y][x]
	ws.board[y][x] = ' '
	defer func() { ws.board[y][x] = c }()

	if x > 0 && ws.board[y][x-1] == ws.word[pos] && ws.exist(x-1, y, pos+1) {
		return true
	}
	if y > 0 && ws.board[y-1][x] == ws.word[pos] && ws.exist(x, y-1, pos+1) {
		return true
	}
	if x < (len(ws.board[0])-1) && ws.board[y][x+1] == ws.word[pos] && ws.exist(x+1, y, pos+1) {
		return true
	}
	if y < (len(ws.board)-1) && ws.board[y+1][x] == ws.word[pos] && ws.exist(x, y+1, pos+1) {
		return true
	}
	return false
}

func exist(board [][]byte, word string) bool {
	ws := &wordSearch{
		board: board,
		word:  word,
	}
	for y := 0; y < len(board); y++ {
		for x := 0; x < len(board[y]); x++ {
			if board[y][x] == word[0] {
				if ws.exist(x, y, 1) {
					return true
				}
			}
		}
	}
	return false
}

func TestWordSearch(t *testing.T) {
	assert.True(t, exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED"))
	assert.True(t, exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "SEE"))
	assert.False(t, exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCB"))
}

func BenchmarkWordSearch(b *testing.B) {
	for n := 0; n < b.N; n++ {
		exist([][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED")
	}
}
