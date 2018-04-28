#include "Gomoku.h"
#include "TdLearner.h"

int main() {
    TdLearner td(0.01, 0.9);
    td.learning(100);
    return 0;
}
