#ifndef TD_LEARNER_H
#define TD_LEARNER_H

#include <map>
#include "Gomoku.h"

using namespace std;

class TdLearner {
    public:
        TdLearner(float eta = 0.01, float gamma = 0.9);
        void learning(int numTrails = 50, 
                map<int, float> weights = {{1,1.0}, {2,2.0}, {3,3.0}, {4,4.0}, {5,5.0}});

    private:
        float eta_;
        float gamma_;
};

#endif
