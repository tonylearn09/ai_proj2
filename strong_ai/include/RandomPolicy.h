#ifndef RANDOM_POLICY_H
#define RANDOM_POLICY_H

#include "Gomoku.h"


class RandomPolicy {
    public:
        RandomPolicy();
        int getNextAction(Gomoku game);
};

#endif
