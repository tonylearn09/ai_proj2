#include "ThreatPattern.h"

using namespace std;

ThreatPattern::ThreatPattern(const vector<int>& pattern_, const vector<int>& patternSquares_) {
    pattern.push_back(pattern_);
    pattern.push_back(switchPattern(pattern_));
    patternSquares = patternSquares_;
}

const vector<int>& ThreatPattern::getPattern(int playerIndex) const {
    return pattern[playerIndex - 1];
}

const vector<int>& ThreatPattern::getPatternSquares() const {
    return patternSquares;
}

vector<int> ThreatPattern::switchPattern(const vector<int>& pattern) {
    vector<int> patternSwitched(pattern.size());
    for(int i = 0; i < pattern.size(); i++) {
        if(pattern[i] == 1) {
            patternSwitched[i] = 2;
        }
    }
    return patternSwitched;
}
