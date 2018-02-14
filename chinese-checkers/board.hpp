
#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <array>
#include <vector>

enum Pebble {
    INVALID = 0, NO_PEBBLE, P1, P2, PEBBLE_NB
};

constexpr std::array<char, PEBBLE_NB + 2> PEBBLE_CHAR = { ' ', '.', 'x', '+'};

struct Hole {
    int x;
    int y;
};

struct Direction {
    int dx;
    int dy;
};

struct Move {
    Hole from;
    Hole to;
};

constexpr int X_SIZE = 19, Y_SIZE = 19;

const std::array<Direction, 6> directions_steps =
{
    Direction{1,  0}, Direction{-1, 0}, Direction{0,  1},
    Direction{0, -1}, Direction{1, -1}, Direction{-1, 1}
};
const std::array<Direction, 6> directions_jumps =
{
    Direction{2,  0}, Direction{-2, 0}, Direction{0,  2},
    Direction{0, -2}, Direction{2, -2}, Direction{-2, 2}
};



class Board {
    std::array<std::array<Pebble, X_SIZE>, Y_SIZE> _squares;
    Pebble _turn;

public:
    // Constructors.
    Board();

    // Moves.
    void do_move(const Move &move);
    void undo_move(const Move &move);
    void generate_moves(std::vector<Move> &moves);
    void generate_jumps(const Hole &from, std::vector<Move> &moves);

    // Score.
    int score() const;
    int dist(const Hole &a, const Hole &b);

    // Board perimiters.
    bool inside_board(int x, int y) const;
    bool inside_P1(int x, int y) const;
    bool inside_P2(int x, int y) const;

    // Helpers.
    Pebble swap(Pebble pebble) const;

    // Display.
    friend std::ostream& operator<<(std::ostream&, const Board&);
};

inline Pebble Board::swap(Pebble pebble) const {
    return pebble == P1 ? P2 : P1;
}

inline bool Board::inside_board(int x, int y) const {
    int sum = x + y;
    return (x <= 13 and y <= 13 and 14 <= sum and sum <= 26)
    or (5 <= x and 5 <= y and 10 <= sum and sum <= 22);
}

inline bool Board::inside_P1(int x, int y) const {
    int sum = x + y;
    return 10 <= x and x <= 13 and 1 <= y and y <= 4
    and 14 <= sum and sum <= 17;
}

inline bool Board::inside_P2(int x, int y) const {
    int sum = x + y;
    return 5 <= x and x <= 8 and 14 <= y and y <= 17
    and 19 <= sum and sum <= 22;
}

#endif /* board_hpp */
