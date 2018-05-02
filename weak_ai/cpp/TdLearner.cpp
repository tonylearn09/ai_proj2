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
        //weights = {{0,0.0}, {1,0.0}, {2,0.0}, {3,0.0}, {4,0.0}, {5,0.0}};
    }

    // Check weight
    cout << "Initial weights: " << "[";
    streamsize ss = std::cout.precision();
    for (auto &x: weights) {
        cout << x.first << ": " << fixed << setprecision(2) << x.second << ", ";
    }
    cout << "]" << endl;
    cout.precision(ss);
}

void TdLearner::learning(int numTrails) {
    MinimaxPolicy agentPolicy(1);
    //RandomPolicy oppoPolicy;
    MinimaxPolicy oppoPolicy(1);

    for (int t = 0; t < numTrails; t++) {
        /*
        if (t % 50 == 0 and t != 0) {
            eta_ = eta_ / 10;
        }
        */
        Gomoku newGame(1);
        vector<int> phi2 = newGame.winningCount[const_agentId - 1];
        //phi2.insert(phi2.end(), newGame.winningCount[const_oppoId-1].begin(),
                //newGame.winningCount[const_oppoId-1].end());
        float Vs2 = 0.0;
        float reward = 0.0;
        bool end_game = false;
        while (1) {
            if (end_game) {
                if (newGame.isEnd() >= 0) {
                    int end_state = newGame.isEnd();
                    if (end_state == 0)
                        reward = 0.0;
                    else if (end_state == 1)
                        reward = 30.0;
                    else if (end_state == 2)
                        reward = -30.0;
                    else

                        cout << "No this end state" << endl;

                }
                for (auto &x: weights) {
                    if (x.first != 0)
                        weights[x.first] = weights[x.first] - eta_ * (Vs2 - reward) * phi2[x.first] / (t + 1);
                        //weights[x.first] = weights[x.first] - eta_ * (Vs2 - reward) * phi2[x.first];
                }
                break;
            }
            int nextPlayer = newGame.nextPlayer;
            float Vs1 = Vs2;
            vector<int> phi1 = phi2;
            int action;
            if (nextPlayer == const_agentId)
                action = agentPolicy.getNextAction(newGame, weights);
            else
                //action = oppoPolicy.getNextAction(newGame);
                action = oppoPolicy.getNextAction(newGame, weights);

            newGame.updateBoard(action);

            phi2 = newGame.winningCount[const_agentId - 1];
            //phi2.insert(phi2.end(), newGame.winningCount[const_oppoId - 1].begin(),
                    //newGame.winningCount[const_oppoId-1].end());

            Vs2 = evalFunc(newGame, weights);

            int end_state = newGame.isEnd();
            /*
            if (end_state >= 0) {
                tuple<int,int,int> state = newGame.currentGame();
                int losePlayer = get<0>(state);
                if (losePlayer == const_agentId)
                    reward = -30;
                else
                    reward = 30;

                if (end_state == 0)
                    reward = 0.0;
                else if (end_state == 1)
                    reward = 30.0;
                else if (end_state == 2)
                    reward = -30.0;
                else
                    cout << "No this end state" << endl;

            }
            */
            for (auto &x: weights) {
                if (x.first != 0)
                    weights[x.first] = weights[x.first] - eta_ * (Vs1 - reward - gamma_ * Vs2) * phi1[x.first] / (t + 1);
                    //weights[x.first] = weights[x.first] - eta_ * (Vs1 - reward - gamma_ * Vs2) * phi1[x.first];
            }
            if (end_state >= 0) {
                end_game = true;
                //break;
            }
        }

        tuple<int,int,int> state = newGame.currentGame();
        int losePlayer = get<0>(state);
        int totalStep0 = get<1>(state);
        //int totalStep1 = get<2>(state);
        int winPlayer = 3 - losePlayer;
        cout << "Trial " << t  << " :" << endl;
        if (newGame.isEnd() != 0)
            cout << ">>>player " << winPlayer << " wins with steps " << totalStep0 << endl;
        else
            cout << ">>>break even!" << endl;
        cout << "lr: " << eta_ << endl;
        cout << "current weights: [";
        streamsize ss = std::cout.precision();
        for (auto &x: weights) {
            cout << x.first << ": " << fixed << setprecision(2) << x.second << ", ";
        }
        cout << "]" << endl;
        cout.precision(ss);
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
