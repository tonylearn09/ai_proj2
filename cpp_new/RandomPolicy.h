#ifndef RANDOM_POLICY_H
#define RANDOM_POLICY_H

#include "Gomoku.h"

using namespace std;

class RandomPolicy {
    public:
        RandomPolicy();
        int getNextAction(Gomoku game);
};

#endif
