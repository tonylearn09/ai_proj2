#ifndef MOVE_H
#define MOVE_H

#include <cstdlib>
#include <functional>
#include <utility>


/**
 * Represents a move or position on the Gomoku board.
 */
class Move {
    /**
     * Create a new move.
     * @param row Row identifer
     * @param col Column identifier
     */ 
    public:
        Move();
        Move(int row_, int col_);
        Move(std::pair<int, int>);

        bool operator==(const Move& rhs) const;

        bool equals(const Move& rhs);

        // data
        int row;
        int col;
};

namespace std {
    template <>
        struct hash<Move> {
            std::size_t operator()(Move const&) const;
        };
}

#endif
