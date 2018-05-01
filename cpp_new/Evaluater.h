#ifndef EVALUATER_H
#define EVALUATER_H

#include <vector>
#include <memory>
#include "Field.h"
#include "State.h"

using namespace std;

class Evaluator {
    public:
        Evaluator();
        /**
         * Evaluate a state from the perspective of the current player.
         * @param state State to evaluate
         * @return Score from the current players perspective
         */
        long evaluateState(const State& state, int depth);
        long evaluateField(const State& state, int row, int col, int index);
    private:
        vector<int> SCORES;

        /**
         * Given some array representing a vertical/horizontal/diagonal direction
         * on the board, calculate a score based on how many possible fives can be
         * formed and in how many moves.
         *
         * @param direction A 1D field array representing a direction on the board
         * @return Score for this direction
         */
        int scoreDirection(const vector<shared_ptr<Field> > &direction, int index);
};

#endif
