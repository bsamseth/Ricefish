
#include "board.hpp"

Board::Board() {
    for (int y = 0; y < Y_SIZE; ++y) {
        _squares[y] = { INVALID };
        for (int x = 0; x < X_SIZE; ++x) {
            if (inside_P1(x, y))
                _squares[y][x] = P1;
            else if (inside_P2(x, y))
                _squares[y][x] = P2;
            else if (inside_board(x, y))
                _squares[y][x] = NO_PEBBLE;
        }
    }
}

bool Board::inside_board(int x, int y) const {
    int sum = x + y;
    return (x <= 13 and y <= 13 and 14 <= sum and sum <= 26)
        or (5 <= x and 5 <= y and 10 <= sum and sum <= 22);
}

bool Board::inside_P1(int x, int y) const {
    int sum = x + y;
    return 10 <= x and x <= 13 and 1 <= y and y <= 4
        and 14 <= sum and sum <= 17;
}

bool Board::inside_P2(int x, int y) const {
    int sum = x + y;
    return 5 <= x and x <= 8 and 14 <= y and y <= 17
        and 19 <= sum and sum <= 22;
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

