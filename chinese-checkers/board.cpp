#include <cassert>

#include "board.hpp"



Board::Board() : _turn(P1) {
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

void Board::do_move(const Move &move) {
    assert(_squares[move.from.y][move.from.x] == _turn);
    _squares[move.to.y][move.to.x] = _squares[move.from.y][move.from.x];
    _squares[move.from.y][move.from.x] = NO_PEBBLE;
    _turn = swap(_turn);
}

void Board::undo_move(const Move &move) {
    _turn = swap(_turn);
    _squares[move.from.y][move.from.x] = _turn;
    _squares[move.to.y][move.to.x] = NO_PEBBLE;
}

void Board::generate_moves(std::vector<Move> &moves) {
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            Hole from = {x, y};
            Pebble &pebble = _squares[y][x];

            if (pebble == _turn) {

                // Generate all single steps.
                for (const Direction &dir : directions_steps) {
                    Hole to = {x + dir.dx, y + dir.dy};
                    if (_squares[to.y][to.x] == NO_PEBBLE)
                        moves.push_back({from, to});
                }

                // Generate all jumps.
                generate_jumps(from, moves);
            }
        }
    }
}

void Board::generate_jumps(const Hole &from, std::vector<Move> &moves) {
    const Pebble original = _squares[from.y][from.x];
    _squares[from.y][from.x] = _turn;

    for (const Direction &dir : directions_steps) {
        Hole over = {from.x +     dir.dx, from.y +     dir.dy};
        Hole to   = {from.x + 2 * dir.dx, from.y + 2 * dir.dy};
        if (    _squares[over.y][over.x] != NO_PEBBLE
            and _squares[over.y][over.x] != INVALID
            and _squares[to.y][to.x] == NO_PEBBLE) {
            moves.push_back({from, to});
            generate_jumps(to, moves);
        }
    }
    _squares[from.y][from.x] = original;
}

std::ostream& operator<<(std::ostream &strm, const Board &b) {
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            strm << PEBBLE_CHAR[b._squares[y][x]] << ' ';
        }
        strm << '\n';
    }
    return strm;
}

