#ifndef STATE_H
#define STATE_H

#include <vector>
#include <stack>
#include <map>
#include <memory>
#include "Move.h"
#include "Field.h"

using namespace std;

/**
 * Internal game state representation for the AI.
 */
class State {
    /* stores a 2D board array representing the status of each
     * field (intersection) on the Gomoku board. A field can either be empty
     * (0), 1/2 (occupied by a player) or 3 which is an out of bounds field,
     * used for detecting that a field is at/near the edge of the board.
     *
     * Board directions are stored in a 4D array. This 4D array maps each field
     * on the board to a set of neighbouring fields, 4 on each side of the
     * stone
     *
     * To get the neighbouring fields, we index as follows:
     * [row][col][direction][field #]
     *
     * [0][0-9] -> Diagonal from top left to bottom right
     * [1][0-9] -> Diagonal from top right to bottom left
     * [2][0-9] -> Horizontal from left to right
     */
    public:
        State();
        /**
         * Return the Zobrist hash for this state, a unique 64-bit long value
         * representing this state. Updated automatically as moves are made/unmade.
         * @return Hash value (Long)
         */
        long long getZobristHash();
        /**
         * Apply a move to this state.
         * @param move Move to apply
         */
        void makeMove(Move move);
        /**
         * Undo a move on this state.
         * @param move Move to undo
         */
        void undoMove(Move move);
        /**
         * Return whether or not this field has occupied fields around it, within
         * some given distance. Used to determine if a field on the board is
         * worth evaluating as a possible move.
         * @param row Field row
         * @param col Field col
         * @param distance How far to look in each direction, limit 4
         * @return 
         */
        bool hasAdjacent(int row, int col, int distance);


        /**
         * Generate the 4D board directions array, by iterating
         * diagonally/horizontally/vertically and storing the references to the
         * neighbouring fields.
         * @param board Field array
         **/
        void generateDirections();

        /**
         * Determine if this state is terminal
         * @return 0 if not terminal, index (1/2) of the player who has won, or 3
         * if the board is full
         */
        int terminal();

        /**
         * Get the total number of moves made on this state
         * @return # of moves
         */
        int getMoves();

        /**
         * Get a field instance on the board at a given row/col position. For
         * unit testing purposes.
         * @param row Row
         * @param col Column
         * @return Field instance at given position
         */
        Field getField(int row, int col);

        void init_board();
        void init_neighbor_map();
        void init_zobristkeys();
        bool is_valid_cell(int row, int col);

        // data
        typedef std::vector<Field> FieldV1;
        typedef std::vector<FieldV1> FieldV2;
        typedef std::vector<FieldV2> FieldV3;
        typedef std::vector<FieldV3> FieldV4;

        vector<vector<Field> > board;
        //vector<vector<vector<vector<Field> > > > directions;
        FieldV4 directions;

        // The current player
        int currentIndex;

         // Zobrist hashing, for using the state in a hash data structure
        long long zobristHash;
        vector<vector<vector<long long> > >  zobristKeys;

        stack<Move> moveStack;

        map<string, pair<int, int> > neighbor_map;


};


#endif
