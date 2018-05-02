#ifndef TD_LEARNER_H
#define TD_LEARNER_H

#include <map>
#include <string>
#include "Gomoku.h"

using namespace std;

class TdLearner {
    public:
        TdLearner(float eta = 0.001, float gamma = 0.9, string weight_filename="weight.txt");
        void learning(int numTrails = 50);

    private:
        void save_weight();
        float eta_;
        float gamma_;
        string weight_filename_;
        map<int, float> weights;
};

#endif
