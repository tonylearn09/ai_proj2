#ifndef MINIMAX_POLICY_H
#define MINIMAX_POLICY_H

#include <utility>
#include <algorithm>
#include <map>
#include "Gomoku.h"
#include <cfloat>

using namespace std;

const int const_agentId = 1;
const int const_oppoId = 2;

class MinimaxPolicy {
    public:
        MinimaxPolicy(int depth_);
        int getNextAction(Gomoku game, map<int, float> weights=map<int, float>());
    private:
        int depth;
        pair<float, int> recurseAlphaBeta(Gomoku game, int d, float lowerBound, float upperBound, map<int, float> weights);

};

float evalFunc(Gomoku game, 
        map<int, float> weights={{0,0.0}, {1,1.0}, {2,4.0}, {3,9.0}, {4,16.0}, {5,25.0}}
);



#endif
