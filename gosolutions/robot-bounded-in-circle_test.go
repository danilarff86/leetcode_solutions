package gosolutions

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func isRobotBounded(instructions string) bool {
	directions := [4]struct{ x, y int }{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
	pos := struct{ x, y, dirIdx int }{0, 0, 0}
	for _, cmd := range instructions {
		switch cmd {
		case 'G':
			pos.x += directions[pos.dirIdx].x
			pos.y += directions[pos.dirIdx].y
		case 'L':
			pos.dirIdx = (pos.dirIdx + 3) % 4
		case 'R':
			pos.dirIdx = (pos.dirIdx + 1) % 4
		}
	}
	return (pos.x == 0 && pos.y == 0) || (pos.dirIdx != 0)
}

func TestRobotBoundedInCircle(t *testing.T) {
	assert.True(t, isRobotBounded("GGLLGG"))
	assert.False(t, isRobotBounded("GG"))
	assert.True(t, isRobotBounded("GL"))
}
