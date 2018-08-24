//
//  search.cpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 14/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#include <cassert>
#include <chrono>

#include "search.hpp"

SearchResult search(Board &board, int secs) {
    auto start_time = std::chrono::steady_clock::now();

    SearchResult result;
    int depth = 1;
    do {
        result = negamax_pruned(board, depth++);
    } while (std::chrono::duration_cast<
                std::chrono::seconds>
             (std::chrono::steady_clock::now() - start_time)
             .count() < secs);
    return result;
}

SearchResult search(Board &board) {
    SearchResult result;
    for (int depth = 1; depth <= 4; ++depth) {
        result = negamax_pruned(board, depth);
        std::cout << " info depth " << depth << " " << result << std::endl;
    }
    return result;
}

SearchResult negamax_pruned(Board &board, int depth, int lower, int upper) {
    if (depth <= 0) {
        return {board.score(), NO_MOVE};
    }

    Move best_move;
    int best_score = std::numeric_limits<int>::min();
    std::vector<Move> moves;
    board.generate_moves(moves);
    for (const Move &move : moves) {
        board.do_move(move);
        int v = -negamax_pruned(board, depth - 1, -upper, -lower).score;
        board.undo_move(move);

        if (v > best_score) {
            best_score = v;
            best_move = move;
        }

        lower = std::max(lower, v);

        if (lower >= upper)
            break;
    }
    return {best_score, best_move};
}
