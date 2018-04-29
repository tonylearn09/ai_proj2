#include <iostream>
#include <fstream>
#include <iomanip>
#include "TdLearner.h"
#include "MinimaxPolicy.h"
#include "RandomPolicy.h"

using namespace std;

TdLearner::TdLearner(float eta, float gamma, string weight_filename) {
    gamma_ = gamma;
    eta_ = eta;
    weight_filename_ = string(weight_filename);

    // Read weight
    ifstream weight_file(weight_filename_.c_str());
    if (weight_file.is_open()) {
        for (int key = 0; key < 6; key++) {
            weight_file >> weights[key];
        }
        weight_file.close();
    } else {
        weights = {{0,0.0}, {1,1.0}, {2,2.0}, {3,3.0}, {4,4.0}, {5,5.0}};
    }

    // Check weight
    cout << "[" << endl;
    for (auto &x: weights) {
        cout << x.first << ": " << fixed << setprecision(2) << x.second << ", ";
    }
    cout << "]" << endl;
}

void TdLearner::learning(int numTrails) {
    MinimaxPolicy agentPolicy(1);
    RandomPolicy oppoPolicy;

    for (int t = 0; t < numTrails; t++) {
        Gomoku newGame(1);
        vector<int> phi2 = newGame.winningCount[const_agentId - 1];
        //phi2.insert(phi2.end(), newGame.winningCount[const_oppoId-1].begin(),
                //newGame.winningCount[const_oppoId-1].end());
        float Vs2 = 0.0;
        float reward = 0.0;
        while (1) {
            int nextPlayer = newGame.nextPlayer;
            float Vs1 = Vs2;
            vector<int> phi1 = phi2;
            int action;
            if (nextPlayer == const_agentId)
                action = agentPolicy.getNextAction(newGame, weights);
            else
                action = oppoPolicy.getNextAction(newGame);

            newGame.updateBoard(action);

            phi2 = newGame.winningCount[const_agentId - 1];
            //phi2.insert(phi2.end(), newGame.winningCount[const_oppoId - 1].begin(),
                    //newGame.winningCount[const_oppoId-1].end());

            Vs2 = evalFunc(newGame, weights);

            if (newGame.isEnd() >= 0) {
                tuple<int,int,int> state = newGame.currentGame();
                int losePlayer = get<0>(state);
                if (losePlayer == const_agentId)
                    reward = -30;
                else
                    reward = 30;
            }
            for (auto &x: weights) {
                weights[x.first] = weights[x.first] - eta_ * (Vs1 - reward - gamma_ * Vs2) * phi1[x.first] / (t + 1);
            }
            if (newGame.isEnd() >= 0)
                break;
        }

        tuple<int,int,int> state = newGame.currentGame();
        int losePlayer = get<0>(state);
        int totalStep0 = get<1>(state);
        //int totalStep1 = get<2>(state);
        int winPlayer = 3 - losePlayer;
        if (newGame.isEnd() != 0)
            cout << ">>>player " << winPlayer << " wins with steps " << totalStep0 << endl;
        else
            cout << ">>>break even!" << endl;
        cout << "current weights: [" << endl;
        for (auto &x: weights) {
            cout << x.first << ": " << fixed << setprecision(2) << x.second << ", ";
        }
        cout << "]" << endl;
    }

    save_weight();

}

void TdLearner::save_weight() {
    // write to file
    ofstream weight_file(weight_filename_.c_str());
    if (weight_file.is_open()) {
        for (auto &x: weights) {
            weight_file << x.second << endl;
        }
        weight_file.close();
    } else {
        cout << "Cannot write to " << weight_filename_ << endl;
    }
}

