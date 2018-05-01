#ifndef NEGAMAXPLAYER_H
#define NEGAMAXPLAYER_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <ctime>
#include "Move.h"
#include "State.h"
#include "Evaluater.h"
#include "Gomoku.h"
#include "ThreatUtils.h"
#include "Cache.h"

using namespace std;

class NegamaxPlayer {
    public:
        NegamaxPlayer();
        Move getMove(Gomoku gameState);
    private:
        /**
         * Generate a list of sorted and pruned moves for this state. Moves are
         * pruned when they are too far away from existing stones, and also when
         * threats are found which require an immediate response.
         * @param state State to get moves for
         * @return A list of moves, sorted and pruned
         */
        vector<Move> getSortedMoves(State state);
         /**
          * Run the negamax algorithm for a node in the game tree.
          * @param state Node to search
          * @param depth Depth to search to
          * @param alpha Alpha bound
          * @param beta Beta bound
          * @return Score of the node
          * @throws InterruptedException Timeout or interrupted by the user
          */
        long negamax(State state, int depth, long alpha, long beta);

        /**
         * Place the best move found from a state into the hash table, replacing
         * an existing entry if the state was searched to a higher depth
         * @param key Hash key of the state
         * @param move Move to save
         * @param depth Depth of the search
         */
        void putMoveEntry(long long key, Move move, int depth);

        /**
         * Run a depth-limited negamax search on a set of moves, sorting them by
         * score.
         * @param depth Depth to search to
         * @return Original move list sorted by best score first
         */
        vector<Move> searchMoves(State state, vector<Move> moves, int depth);

        /**
         * Run negamax for an increasing depth, sorting the moves after every
         * completed search
         * @param startDepth Start depth
         * @param endDepth Maximum depth
         * @return Best move found
         */
        Move iterativeDeepening(int startDepth, int endDepth);

        /*
         * Check if no more time for search
         */
        bool time_out();

        class MoveEntry {
            public:
                MoveEntry(): depth(-1) { }
                MoveEntry(Move move_, int depth_): move(move_), depth(depth_) {}
                Move move;
                int depth;
        };

        class ScoredMove {
            public:
                ScoredMove(Move move_, long score_): move(move_), score(score_) {}

                // Make descending order of score
                bool operator<(const ScoredMove& rhs) const {
                    return (score > rhs.score);
                }
                Move move;
                long score;
        };

        ThreatUtils reducer;
        Evaluator evaluator;
        Cache<long long, MoveEntry> moveTable;

        float max_time;
        time_t startTime;

        long totalNodeCount;
        long nonLeafCount;
        long branchesExploredSum;

        State state;

};

#endif
