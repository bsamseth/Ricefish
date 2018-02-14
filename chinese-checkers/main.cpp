//
//  main.cpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 13/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#include <iostream>
#include "board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    Board board;
    std::vector<Move> moves;
    board.generate_moves(moves);
    for (const Move &move : moves) {
        board.do_move(move);
        cout << board << endl;
        board.undo_move(move);
    }
    return 0;
}
