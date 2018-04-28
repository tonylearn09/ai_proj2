#include <iostream>
#include "TdLearner.h"
#include "MinimaxPolicy.h"
#include "RandomPolicy.h"

using namespace std;

TdLearner::TdLearner(Gomoku game, float eta, float gamma) {
    gamma_ = gamma;
    eta_ = eta;
    game_ = game;
}

void TdLearner::learning(int numTrails, map<int, float> weights) {
    agentPolicy = MinimaxPolicy();
    oppoPolicy = RandomPolicy();

    for (int t = 0; t < numTrails; t++) {
        Gomoku newGame(1);
        vector<int> phi2 = newGame.winningCount[const_agentId - 1];
        phi2.insert(phi2.end(), newGame.winningCount[const_oppoId-1].begin(),
                newGame.winningCount[const_oppoId-1].end());
        float Vs2 = 0;
        float reward = 0;
        while (1) {
            nextPlayer = newGame.nextPlayer;
            float Vs1 = Vs2;
            vector<int> phi1 = phi2;
            if (nextPlayer == const_agentId)
                action = agentPolicy.getNextAction(newGame, weights);
            else
                action = oppoPolicy.getNextAction(newGame);

            newGame.updateBoard(action)

            phi2 = newGame.winningCount[const_agentId - 1];
            phi2.insert(phi2.end(), newGame.winningCount[const_oppoId - 1].begin(),
                    newGame.winningCount[const_oppoId-1].end());

            Vs2 = evalFunc(newGame, weights);

            if newGame.isEnd() >= 0:
                tuple<int,int,int> state = newGame.currentGame();
                int losePlayer = get<0>(state);
                if (losePlayer == const_agentId)
                    reward = -30;
                else
                    reward = 30;
            for (auto &x: weights) {
                weights[x.first] = weights[x.first] - eta_ * (Vs1 - reward - gamma_ * Vs2) * phi1[x.first] / (t + 1)
                    if (newGame.isEnd() >= 0)
                        break;
            }
        }

        tuple<int,int,int> state = newGame.currentGame();
        int losePlayer = get<0>(state);
        int totalStep0 = get<1>(state);
        //int totalStep1 = get<2>(state);
        winPlayer = 3 - losePlayer;
        if (newGame.isEnd() != 0)
            cout << ">>>player " << winPlayer << " wins with steps " << totalStep0 << endl;
        else
            cout << ">>>break even!" << endl;
        cout << "current weights: " << endl;
        for (auto &x: weights) {
            cout << x.first << ": " << fixed << setprecision(2) << x.second << ", ";
        }
        cout << endl;
    }

}

