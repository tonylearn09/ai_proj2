#include "../include/Field.h"

Field::Field() {
    row = 0;
    col = 0;
    index = 3;
}

Field::Field(int row_, int col_) {
    row = row_;
    col = col_;
    index = 0;
}
