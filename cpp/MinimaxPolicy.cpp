#include "MinimaxPolicy.h"
using namespace std;

MinimaxPolicy::MinimaxPolicy(int depth_) {
    depth = depth_;
}

int MinimaxPolicy::getNextAction(Gomoku game, map<int, float> weights) {
    pair<float, int> val_act = recurseAlphaBeta(game, 0, -FLT_MAX, FLT_MAX, weights);
    return val_act.second;
} 


pair<float, int> MinimaxPolicy::recurseAlphaBeta(Gomoku game, int d, 
        float lowerBound, float upperBound, map<int, float> weights) {
    int winner = game.isEnd();

    if (winner == const_agentId)
        return make_pair(FLT_MAX*0.9, -1);
    else if (winner == const_oppoId)
        return make_pair(-FLT_MAX*0.9, -1);
    else if (winner == 0)
    	return make_pair(0.0, -1);

    if (d == depth) {
        if (weights.empty())
            return make_pair(evalFunc(game), -1);
        else
            return make_pair(evalFunc(game, weights), -1);
    }

    vector<vector<int> > gomokuboard = game.gomokuboard;
    tuple<int, int> lastMove = game.lastMove;
    int player = game.nextPlayer;

    int nextd;
    
    if (player == const_oppoId)
        nextd = d + 1;
    else
        nextd = d;
  
    /*
    vector<pair<float, int> > choices;
    for (int k = 0; k < 217; k++) {
        res = game.updateBoard(k);
        if (res) {
            // have update
            if (weights.empty()) 
                choices.push_back(make_pair(self.evalFunc(game), k));
            else
                choices.push_back(make_pair(self.evalFunc(game, weights), k));
            game.revert(lastMove)
        }
    }
    */


    //sort(choices.begin(), choices.end());
    //if (player == const_agentId)
        //reverse(choices.begin(), choices.end());

    pair<float, int> maxPair = make_pair(-FLT_MAX, -1);
    pair<float, int> minPair = make_pair(FLT_MAX, -1);
    for (int k = 0; k < 217; k++) {
        bool res = game.updateBoard(k);
        if (res) {
            pair<float, int> r_val_act;
            if (player == const_agentId) {
                r_val_act = recurseAlphaBeta(game, nextd, lowerBound, upperBound, weights);
                float v = r_val_act.first;
                if (v > maxPair.first)
                	maxPair = make_pair(v, k);
                
            } else {
                r_val_act = recurseAlphaBeta(game, nextd, lowerBound, upperBound, weights);
                float v = r_val_act.first;
                if (v < minPair.first)
                	minPair = make_pair(v, k);
            }

            game.revert(lastMove);
            if (player == const_agentId && maxPair.first >= upperBound)
                return maxPair;
            else if (player != const_agentId && minPair.first <= lowerBound)
                return minPair;

            if (player == const_agentId)
                lowerBound = max(lowerBound, maxPair.first);
            else
                upperBound = min(upperBound, minPair.first);
        }
    }

    if (player == const_agentId)
        return maxPair;
    else
        return minPair;

}

float evalFunc(Gomoku game, map<int, float> weights) {
    vector<int> agentCount = game.winningCount[const_agentId - 1];
    vector<int> oppoCount = game.winningCount[const_oppoId - 1];

    float total = 0.0;
    for (auto const& x : weights) {
        total += x.second * agentCount[x.first];
        total -= x.second * oppoCount[x.first];
        
    }
    return total;
}
