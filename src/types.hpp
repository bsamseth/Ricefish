//
//  types.hpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 14/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#ifndef types_h
#define types_h

#include <array>

enum Pebble {
    INVALID = 0, NO_PEBBLE, P1, P2, PEBBLE_NB
};

constexpr std::array<char, PEBBLE_NB + 2> PEBBLE_CHAR = { ' ', '.', 'x', '+'};

struct Hole {
    int x;
    int y;
};

constexpr Hole P1_HOME = {13, 1};
constexpr Hole P2_HOME = {5, 17};

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

#endif /* types_h */
