//
//  search.hpp
//  chinese-checkers
//
//  Created by Bendik Samseth on 14/02/2018.
//  Copyright © 2018 Bendik Samseth. All rights reserved.
//

#ifndef search_hpp
#define search_hpp

#include <limits>

#include "types.hpp"
#include "board.hpp"

struct SearchResult {
    int score;
    Move move;
};

SearchResult search(Board &board, int max_depth);

SearchResult negamax_pruned(Board &board,
                            int depth,
                            int lower = std::numeric_limits<int>::min(),
                            int upper = std::numeric_limits<int>::max());

inline std::ostream& operator<<(std::ostream &strm, const SearchResult &s) {
    return strm << "score " << s.score << " move " << s.move;
}


#endif /* search_hpp */
