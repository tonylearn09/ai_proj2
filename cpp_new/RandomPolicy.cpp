#include <ctime>
#include "RandomPolicy.h"
#include "Move.h"

using namespace std;

RandomPolicy::RandomPolicy() {
    srand(time(NULL));
}

int RandomPolicy::getNextAction(Gomoku game) {
    int agent = game.getCurrentIndex();
    while (1) { 
        int pos = rand() % static_cast<int>(217);
        Move pair = game.index_map[pos];

        if (game.boardState(pair.row, pair.col) == 0)
            return pos;
    }
}
