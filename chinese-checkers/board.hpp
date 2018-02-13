
#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <array>

enum Pebble {
    INVALID = 0, NO_PEBBLE, P1, P2, PEBBLE_NB = 2
};

constexpr std::array<char, PEBBLE_NB + 2> PEBBLE_CHAR = { ' ', '.', 'x', '+'};


class Board {
    constexpr static int X_SIZE = 19, Y_SIZE = 19;
    std::array<std::array<Pebble, X_SIZE>, Y_SIZE> _squares;
    Pebble _turn;
    
public:
    
    Board();
    
    bool inside_board(int x, int y) const;
    bool inside_P1(int x, int y) const;
    bool inside_P2(int x, int y) const;
    
    friend std::ostream& operator<<(std::ostream&, const Board&);
};


#endif /* board_hpp */
