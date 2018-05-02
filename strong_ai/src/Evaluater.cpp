#include "../include/Evaluater.h"

Evaluator::Evaluator() {
    SCORES = {19, 15, 11, 7, 3};
}


int Evaluator::scoreDirection(const vector<shared_ptr<Field> > &direction, int index) {
    int score = 0;
    // Pass a window of 5 across the field array
    for(int i = 0; (i + 4) < direction.size(); i++) {
        int empty = 0;
        int stones = 0;
        for(int j = 0; j <= 4; j++) {
            if(direction[i + j]->index == 0) {
                empty++;
            } else if(direction[i + j]->index == index) {
                stones++;
            } else {
                // Opponent stone in this window, can't form a five
                break;
            }
        }
        // Ignore already formed fives, and empty windows
        if(empty == 0 || empty == 5) continue;

        // Window contains only empty spaces and player stones, can form
        // a five, get score based on how many moves needed
        if(stones + empty == 5) {
            score += SCORES[empty];
        }
    }
    return score;
}

long Evaluator::evaluateState(const State& state, int depth) {
    int playerIndex = state.currentIndex;
    //int opponentIndex = playerIndex == 1 ? 2 : 1;
    int opponentIndex = 3 - playerIndex;

     // Check for a winning/losing position
    int terminal = state.terminal();
    if(terminal == playerIndex) return 10000 + depth;
    if(terminal == opponentIndex) return -10000 - depth;

    // Evaluate each field separately, subtracting from the score if the
    // field belongs to the opponent, adding if it belongs to the player
    long score = 0;
    for(int i = 0; i < state.board.size(); i++) {
        for(int j = 0; j < state.board[i].size(); j++) {
            if((state.board[i][j])->index == opponentIndex) {
                score -= evaluateField(state, i, j, opponentIndex);
            } else if((state.board[i][j])->index == playerIndex) {
                score += evaluateField(state, i, j, playerIndex);
            }
        }
    }
    return score;

}
long Evaluator::evaluateField(const State& state, int row, int col, int index) {
    long score = 0;
    for(int direction = 0; direction < 3; direction++) {
        score += scoreDirection(state.directions[row][col][direction],
                index);
    }
    return score;
}

