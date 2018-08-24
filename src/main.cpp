//
//  main.cpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 13/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#include <iostream>
#include "board.hpp"
#include "search.hpp"
#include "interface.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    Board board(INITIAL_POSITION);
    //search(board);
    cout << board.score() << endl;
    cout << board << endl;
    self_play();
    return 0;
}
