
#include <iostream>
#include <string>
#include <algorithm>

#include "interface.hpp"
#include "types.hpp"
#include "board.hpp"
#include "search.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;


void play() {
    Board board;
    string input;
    while (true) {
        cout << '\n' << board << endl;

        // We query the user until she enters a legal move.
        Move m;
        std::vector<Move> move_list;
        board.generate_moves(move_list);
        while (std::find(move_list.begin(), move_list.end(), m) == move_list.end()) {
            printf("Your move:  ");
            getline(cin, input);
            try {
                cout << "the input: " << input << endl;
                char fx = input[0], fy = input[1];
                char tx = input[2], ty = input[3];
                m = {{fx-'0', fy-'0'}, {tx-'0', ty-'0'}};
            } catch(const std::out_of_range &err) {
                printf("Input a move like 3 for top right (or type q to quit)\n");
            }
        }
        cout << "Parsed: " << m << endl;
        board.do_move(m);

        std::cout << '\n' << board << std::endl;


        SearchResult result = search(board, 5);
        cout << "My move: " << result.move << endl;
        board.do_move(result.move);
    }
}

void self_play() {
    Board board;
    cout << board << endl;
    do {
        SearchResult result = search(board);
        board.do_move(result.move);
        cout << board << "\nScore: " << board.score_absolute(result.score) << endl;
    } while (true);
}
