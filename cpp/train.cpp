#include "Gomoku.h"
#include "TdLearner.h"
#include <time.h>

int main() {
    
    srand((unsigned)time(NULL));
    TdLearner td(0.01, 0.9, "weight.txt");
    td.learning(50);
    return 0;
}
