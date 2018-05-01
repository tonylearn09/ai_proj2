#include "Move.h"

Move::Move() {
    row = -1;
    col = -1;
}

Move::Move(int row_, int col_) {
    row = row_;
    col = col_;
}

Move::Move(std::pair<int, int> index) {
    row = index.first;
    col = index.second;
}


bool Move::operator==(const Move& rhs) const {
    return (row == rhs.row) && (col == rhs.col);
}

bool Move::equals(const Move& rhs) {
    return (row == rhs.row) && (col == rhs.col);
}

std::size_t std::hash<Move>::operator()(Move const& m) const {
    size_t h1 ( std::hash<int>{}(m.row) );
    size_t h2 ( std::hash<int>{}(m.col) );
    return h1 ^ (h2 << 1);
}

