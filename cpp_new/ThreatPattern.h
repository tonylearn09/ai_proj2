#ifndef THREATPATTERN_H
#define THREATPATTERN_H

#include <vector>
using namespace std;

class ThreatPattern {
    public:
        /**
         * Create a new threat pattern.
         * @param pattern Pattern represented as a 1D array, where 0 is an
         *      empty space and 1 refers to a stone being present
         * @param patternSquares The offensive/defensive squares of the
         *      threat, i.e. the indices of all 0's in the
         *      pattern array
         */
        ThreatPattern(const vector<int>& pattern, const vector<int>&  patternSquares);
        /**
         * Get the pattern from the perspective of a player.
         * @param playerIndex Player identifier
         * @return Pattern array
         */
        const vector<int>& getPattern(int playerIndex) const;
        /**
         * Return the offensive/defensive square indices in the pattern.
         * @return int[] containing all the square indices
         */
        const vector<int>& getPatternSquares() const;
    private:
        /**
         * Convert an input pattern to player 2's perspective.
         * @param pattern Input pattern array
         * @return Same array with every 1 turned into a 2
         */
        vector<int> switchPattern(const vector<int>& pattern);
        vector<vector<int> >  pattern;
        vector<int> patternSquares;
};

#endif
