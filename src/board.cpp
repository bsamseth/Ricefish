#include <cassert>
#include <cmath>
#include <iomanip>

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

std::ostream& operator<<(std::ostream &strm, const Board &b) {
    for (int y = 0; y < Y_SIZE; ++y) {
        strm << std::setw(2) << y << "|";
        for (int x = 0; x < X_SIZE; ++x) {
            strm << PEBBLE_CHAR[b._squares[y][x]] << ' ';
        }
        strm << '\n';
    }

    // For printing the x-axis, the numbers 10 to 18 are printed
    // using the chars after '9', as without this they would be
    // two symbols wide and not align with the drawing of the board.
    strm << "   ";
    for (int x = 0; x < X_SIZE; ++x) strm << "--";
    strm << "\n   ";
    for (char x = 0; x < X_SIZE; ++x) {
        strm << (char)('0'+x) << ' ';
    }
    return strm;
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
                generate_jumps(from, from, moves);
            }
        }
    }
}

void Board::generate_jumps(const Hole &origin,
                           const Hole &from,
                           std::vector<Move> &moves) {
    const Pebble original = _squares[from.y][from.x];
    _squares[from.y][from.x] = _turn;

    for (const Direction &dir : directions_steps) {
        Hole over = {from.x +     dir.dx, from.y +     dir.dy};
        Hole to   = {from.x + 2 * dir.dx, from.y + 2 * dir.dy};
        if (    _squares[over.y][over.x] != NO_PEBBLE
            and _squares[over.y][over.x] != INVALID
            and _squares[to.y][to.x] == NO_PEBBLE) {
            moves.push_back({origin, to});
            generate_jumps(origin, to, moves);
        }
    }
    _squares[from.y][from.x] = original;
}

int Board::score() const {
    return _turn == P1 ?  score_by_side<P1>()
                        : score_by_side<P2>();
}


int Board::dist(const Hole &a, const Hole &b) const {
    int diag_steps = 0;
    int dx = a.x - b.x, dy = a.y - b.y;
    int adx = std::abs(dx), ady = std::abs(dy);
    if (dx * dy < 0) {
        diag_steps = std::min(adx, ady);
    }
    return adx + ady - diag_steps;
}

template<Pebble Us>
int Board::score_by_side() const {
    constexpr const Pebble Them = Us == P1 ? P2 : P1;
    constexpr const Hole &our_goal   = Us == P1 ? P2_HOME : P1_HOME;
    constexpr const Hole &their_goal = Us == P1 ? P1_HOME : P2_HOME;

    int our_dist = 0, their_dist = 0;
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            if (_squares[y][x] == Us)
                our_dist += dist({x, y}, our_goal);
            else if (_squares[y][x] == Them)
                their_dist += dist({x, y}, their_goal);
        }
    }
    return their_dist - our_dist;
}


