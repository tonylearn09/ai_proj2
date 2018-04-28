#ifndef MINIMAX_POLICY_H
#define MINIMAX_POLICY_H

#include <utility>
#include <algorithm>
#include <map>
#include "Gomoku.h"

using namespace std;

const int const_agentId = 1;
const int const_oppoId = 2;

class MinimaxPolicy {
    public:
        MinimaxPolicy();
        int getNextAction(Gomoku game, map<int, int> weights);
    private:
        int depth;
        pair<float, int> recurseAlphaBeta(Gomoku game, int d, float lowerBound, float upperBound, map<int, int> weights, 
                int initial_player);

};

int evalFunc(Gomoku game, map<int, float> weights=
        {{1,1.0}, {2,2.0}, {3,3.0}, {4,4.0}, {5,5.0}}
    );

#endif
