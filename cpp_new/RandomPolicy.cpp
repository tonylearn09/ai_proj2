#include <ctime>
#include "RandomPolicy.h"

using namespace std;

RandomPolicy::RandomPolicy() {
    srand(time(NULL));
}

int RandomPolicy::getNextAction(Gomoku game) {
    int agent = game.getCurrentIndex();
    while (1) { 
        int pos = rand() % static_cast<int>(217);
        tuple<int, int> pair = game.index_map[pos];
        int x = get<0>(pair);
        int y = get<1>(pair);

        if (game.boardState(x, y) == 0)
            return pos;
    }
}
