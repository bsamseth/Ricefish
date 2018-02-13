
#include "board.hpp"

Board::Board() {
    for (int x = 0; x < X_SIZE; ++x) {
        _squares[x] = { INVALID };
        for (int y = 0; y < Y_SIZE; ++y) {
            if (inside_board(x, y))
                _squares[x][y] = NO_PEBBLE;
        }
    }
}

bool Board::inside_board(int x, int y) {
    int sum = x + y;
    return (x <= 13 and y <= 13 and 14 <= sum and sum <= 26)
        or (5 <= x and 5 <= y and 10 <= sum and sum <= 22);
}

std::ostream& operator<<(std::ostream &strm, const Board &b) {
    for (int x = 0; x < b.X_SIZE; ++x) {
        for (int y = 0; y < b.Y_SIZE; ++y) {
            strm << PEBBLE_CHAR[b._squares[x][y]] << ' ';
        }
        strm << '\n';
    }
    return strm;
}

