#include "ThreatUtils.h"


ThreatUtils::ThreatUtils() {
    THREES.push_back(ThreatPattern({0, 1, 1, 1, 0, 0}, {0, 4, 5}));
    THREES.push_back(ThreatPattern({0, 0, 1, 1, 1, 0}, {0, 1, 5}));
    THREES.push_back(ThreatPattern({0, 1, 0, 1, 1, 0}, {0, 2, 5}));
    THREES.push_back(ThreatPattern({0, 1, 1, 0, 1, 0}, {0, 3, 5}));

    FOURS.push_back(ThreatPattern({1, 1, 1, 1, 0}, {4}));
    FOURS.push_back(ThreatPattern({1, 1, 1, 0, 1}, {3} ));
    FOURS.push_back(ThreatPattern({1, 1, 0, 1, 1},{2} ));
    FOURS.push_back(ThreatPattern({1, 0, 1, 1, 1}, {1} ));
    FOURS.push_back(ThreatPattern({0, 1, 1, 1, 1}, {0} ));

    REFUTATIONS.push_back(ThreatPattern({1, 1, 1, 0, 0}, {3, 4}));
    REFUTATIONS.push_back(ThreatPattern({1, 1, 0, 0, 1},{2, 3} ));
    REFUTATIONS.push_back(ThreatPattern({1, 0, 0, 1, 1}, {1, 2} ));
    REFUTATIONS.push_back(ThreatPattern({0, 0, 1, 1, 1}, {0, 1} ));
}

vector<Move> ThreatUtils::getThrees(const State& state, const shared_ptr<Field>& field, int playerIndex) {
    return getThreatMoves(THREES, state, field, playerIndex);
}

vector<Move> ThreatUtils::getFours(const State& state, const shared_ptr<Field>& field, int playerIndex) {
    return getThreatMoves(FOURS, state, field, playerIndex);
}

vector<Move> ThreatUtils::getRefutations(const State& state, const shared_ptr<Field>& field, int playerIndex) {
    return getThreatMoves(REFUTATIONS, state, field, playerIndex);
}


vector<Move> ThreatUtils::getThreatMoves(const vector<ThreatPattern>& patternList, const State&
        state, const shared_ptr<Field>& field, int playerIndex) {
    vector<Move> threatMoves;
    // Loop around the field in every direction
    // (diagonal/horizontal/vertical)
    for(int direction = 0; direction < 3; direction++) {
        vector<shared_ptr<Field> > directionArray = state.directions[field->row][field->col][direction];
        for(const ThreatPattern& pattern : patternList) {
            // Try to find the pattern
            int patternIndex = matchPattern(directionArray, pattern.getPattern(playerIndex));
            if(patternIndex != -1) {
                // Found pattern, get the squares in the pattern and map
                // them to moves on the board
                for(int patternSquareIndex : pattern.getPatternSquares()) {
                    Field patternSquareField = *(directionArray[patternIndex + patternSquareIndex]);
                    threatMoves.push_back(Move(patternSquareField.row,
                                patternSquareField.col));
                }
            }
        }
    }
    return threatMoves;
}

int ThreatUtils::matchPattern(const vector<shared_ptr<Field> >& direction, const vector<int>& pattern) {
    for(int i = 0; i < direction.size(); i++) {
        // Check if the pattern lies within the bounds of the direction
        if(i + (pattern.size() - 1) < direction.size()) {
            int count = 0;
            for(int j = 0; j < pattern.size(); j++) {
                if(direction[i + j]->index == pattern[j]) {
                    count++;
                } else {
                    break;
                }
            }
            // Every element was the same, return the start index
            if(count == pattern.size()) {
                return i;
            }
        } else {
            break;
        }
    }
    return -1;
}
