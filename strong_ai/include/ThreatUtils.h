#ifndef THREATUTILS_H
#define THREATUTILS_H

#include <vector>
#include <memory>
#include "ThreatPattern.h"
#include "Move.h"
#include "State.h"
#include "Field.h"


class ThreatUtils {
    public:
        /**
         * Used to search for threats in a Gomoku game. Threats exist around an
         * existing stone on the board and so we only need to search 4 fields in
         * every direction to find the threat.
         */
        ThreatUtils();
        /**
         * Check a field for a broken three or a straight three pattern on the
         * board (0XXX0 and 0X0XX0) belonging to a player.
         * @param playerIndex Player index
         * @return List of moves corresponding to the offensive squares of the
         * threat
         */
        std::vector<Move> getThrees(const State& state, const std::shared_ptr<Field>& field, int playerIndex);
        /**
         * Check a field for a broken three or a straight three pattern on the
         * board (0XXX0 and 0X0XX0) belonging to a player.
         * @param playerIndex Player index
         * @return List of moves corresponding to the offensive/defensive squares of
         * the threat
         */
        std::vector<Move> getFours(const State& state, const std::shared_ptr<Field>& field, int playerIndex);
        /**
         * Check a field for a pattern which can turn into a four, e.g. 00XXX
         * @param playerIndex Player index
         * @return List of moves corresponding to the offensive/defensive squares of
         * the refutation
         */
        std::vector<Move> getRefutations(const State& state, const std::shared_ptr<Field>& field, int playerIndex);
    private:
        /**
         * Search for threats around a field in a game state, mapping each threat
         * to offensive/defensive moves if found.
         * @param patternList List of ThreatPattern objects to search for
         * @param state State to search
         * @param field Field to search around
         * @param playerIndex Player index to search for
         * @return
         */
        std::vector<Move> getThreatMoves(const std::vector<ThreatPattern>& patternList, const State&
                state, const std::shared_ptr<Field>& field, int playerIndex);
        /**
         * Search for a pattern in a field array.
         * @param direction Field array
         * @param pattern Pattern to match e.g. [2 0 2 2]
         * @return The starting index if found, or -1 if not found
         */
        int matchPattern(const std::vector<std::shared_ptr<Field> >& direction, const std::vector<int>& pattern);
        std::vector<ThreatPattern> THREES;
        std::vector<ThreatPattern> FOURS;
        std::vector<ThreatPattern> REFUTATIONS;
};

#endif
