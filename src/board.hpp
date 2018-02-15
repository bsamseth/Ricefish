
#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>
#include <string>

#include "types.hpp"

const std::string INITIAL_POSITION =
            "1"
           "11"
          "111"
         "1111"
    "0000000000000"
    "000000000000"
    "00000000000"
    "0000000000"
    "000000000"
   "0000000000"
  "00000000000"
 "000000000000"
"0000000000000"
    "2222"
    "222"
    "22"
    "2";

const std::string ONE_BEST_JUMP_P1 =
            "1"
           "10"
          "110"
         "1110"
    "0000000100000"
    "000000100000"
    "00000000000"
    "0000001000"
    "000000000"
   "0000000000"
  "00000000000"
 "000000000000"
"0000000000000"
    "2222"
    "222"
    "22"
    "2";

const std::string ONE_BEST_JUMP_P2 =
            "1"
           "11"
          "111"
         "1111"
    "0000000000000"
    "000000000000"
    "00000000000"
    "0000000000"
    "000000000"
   "0000200000"
  "00000000000"
 "000002000000"
"0000020000000"
    "0222"
    "022"
    "02"
    "2";

constexpr int GAME_WON = 100000;  // A score larger than any non-won game score.

class Board {
    std::array<std::array<Pebble, X_SIZE>, Y_SIZE> _squares;
    Pebble _turn;

public:
    // Constructors.
    Board();
    Board(std::string board_string, Pebble turn = P1);

    // Moves.
    void do_move(const Move &move);
    void undo_move(const Move &move);
    void generate_moves(std::vector<Move> &moves);
    void generate_jumps(const Hole &origin,
                        const Hole &from,
                        std::vector<Move> &moves);

    // Score.
    int score() const;
    template<Pebble Us>
    int score_by_side() const;
    int score_absolute(int score) const;
    int dist(const Hole &a, const Hole &b) const;

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
