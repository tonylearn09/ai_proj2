#include "ThreatPattern.h"



ThreatPattern::ThreatPattern(vector<int> pattern_, vector<int> patternSquares_) {
    pattern.push_back(pattern_);
    pattern.push_back(switchPattern(pattern_));
    patternSquares = patternSquares_;
}

vector<int>& ThreatPattern::getPattern(int playerIndex) {
    return pattern[playerIndex - 1];
}

vector<int>& ThreatPattern::getPatternSquares() {
    return patternSquares;
}

vector<int> ThreatPattern::switchPattern(vector<int> pattern) {
    vector<int> patternSwitched(pattern.size());
    for(int i = 0; i < pattern.size(); i++) {
        if(pattern[i] == 1) {
            patternSwitched[i] = 2;
        }
    }
    return patternSwitched;
}
