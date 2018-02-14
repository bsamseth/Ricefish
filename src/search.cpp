//
//  search.cpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 14/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#include "search.hpp"

SearchResult search(Board &board, int max_depth) {
    SearchResult result;
    for (int depth = 0; depth <= max_depth; ++depth) {
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
