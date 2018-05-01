#include <algorithm>
#include <unordered_set>
#include <climits>
#include <ctime>
#include <iostream>
#include "NegamaxPlayer.h"


using namespace std;

NegamaxPlayer::NegamaxPlayer() {
    // Set maximum allowable time to 4.0s
    max_time = 4.0;
    moveTable.setMaxSize(1000000);
}

vector<Move> NegamaxPlayer::getSortedMoves(const State &state) {
    // Board is empty, return a move in the middle of the board
    if(state.getMoves() == 0) {
        vector<Move> moves;
        moves.push_back(Move(8, 9));
        return moves;
    }

    int playerIndex = state.currentIndex;
    int opponentIndex = state.currentIndex == 2 ? 1 : 2;

    unordered_set<Move> fours;
    unordered_set<Move> refutations;

    unordered_set<Move> opponentFours;
    unordered_set<Move> opponentThrees;

    // Check for threats first and respond to them if they exist
    for(int i = 0; i < state.board.size(); i++) {
        for(int j = 0; j < state.board[i].size(); j++) {
            if((state.board[i][j])->index == opponentIndex) {
                vector<Move> four_result = reducer.getFours(state,
                        state.board[i][j], opponentIndex);
                opponentFours.insert(four_result.begin(), four_result.end());
                vector<Move> three_result = reducer.getThrees(state,
                        state.board[i][j], opponentIndex);
                opponentThrees.insert(three_result.begin(), three_result.end());
            }
            else if((state.board[i][j])->index == playerIndex) {
                vector<Move> four_result = reducer.getFours(state,
                        state.board[i][j], playerIndex);
                fours.insert(four_result.begin(), four_result.end());
                vector<Move> refutation_res = reducer.getRefutations(state,
                        state.board[i][j], playerIndex);
                refutations.insert(refutation_res.begin(), refutation_res.end());
            }
        }
    }

    // We have a four on the board, play it
    if(!fours.empty()) {
        return vector<Move>(fours.begin(), fours.end());
    }
    // Opponent has a four, defend against it
    if(!opponentFours.empty()) {
        return vector<Move>(opponentFours.begin(), opponentFours.end());
    }
    // Opponent has a three, defend against it and add refutation moves
    if(!opponentThrees.empty()) {
        opponentThrees.insert(refutations.begin(), refutations.end());
        return vector<Move>(opponentThrees.begin(), opponentThrees.end());
    }

    vector<ScoredMove> scoredMoves;
    

    int key_count = moveTable.count(state.getZobristHash());
    MoveEntry entry = moveTable.get(state.getZobristHash());

    for(int i = 0; i < state.board.size(); i++) {
        for(int j = 0; j < state.board[i].size(); j++) {
            // Ignore hash move
            if(key_count > 0 &&
                    (i == entry.move.row && j == entry.move.col)) {
                continue;
            }
            if((state.board[i][j])->index == 0) {
                if(state.hasAdjacent(i, j, 2)) {
                    int score = evaluator.evaluateField(state, i, j,
                            state.currentIndex);
                    scoredMoves.push_back(ScoredMove(Move(i, j), score));
                    //cout << "( " << i << ", " << j << ")" << "is good" <<endl;
                }
            }
            /*
            if ((state.board[i][j])->index == 1) {
                cout << "( " << i << ", " << j << ")" << "is 1" <<endl;
                for (int m = 0; m < 3; m++) {
                    for (int n = 0; n < 9; n++) {
                        cout << "(" << (state.directions[i][j][m][n])->row << ", " << (state.directions[i][j][m][n])->col << ")" << 
                            ": " << (state.directions[i][j][m][n])->index << endl;
                    }
                }
            }
            */
        }
    }

    vector<Move> moves;

    // Sort based on move score
    sort(scoredMoves.begin(), scoredMoves.end());
    for(ScoredMove move : scoredMoves) {
        moves.push_back(move.move);
    }

    return moves;

}

long NegamaxPlayer::negamax(State& state, int depth, long alpha, long beta) {

    if (time_out()) {
        throw string("time out");
    }

    //totalNodeCount++;
    if (state.terminal() != 0 || depth == 0) {
        return evaluator.evaluateState(state, depth);
    }
    //nonLeafCount++;

    int value;
    long best = LONG_MIN;
    long count = 0;

    Move bestMove;

    // Try the move from a previous search
    int key_count = moveTable.count(state.getZobristHash());
    MoveEntry hashMoveEntry = moveTable.get(state.getZobristHash());

    if (key_count > 0) {
        count++;
        state.makeMove(hashMoveEntry.move);
        try {
            value = -negamax(state, depth - 1, -beta, -alpha);
        } catch (string e) {
            throw e;
        }
        state.undoMove(hashMoveEntry.move);
        if (value > best) {
            bestMove = hashMoveEntry.move;
            best = value;
        }
        if (best > alpha) alpha = best;
        if (best >= beta) return best;
    }

    // No cut-off from hash move, get sorted moves
    vector<Move> moves = getSortedMoves(state);

    for (Move &move : moves) {
        count++;
        state.makeMove(move);
        try {
            value = -negamax(state, depth - 1, -beta, -alpha);
        } catch (string e) {
            throw e;
        }
        state.undoMove(move);
        if(value > best) {
            bestMove = move;
            best = value;
        }
        if(best > alpha) alpha = best;
        if(best >= beta) {
            break;
        }
    }
    //branchesExploredSum += count;
    putMoveEntry(state.getZobristHash(), bestMove, depth);
    return best;
}



void NegamaxPlayer::putMoveEntry(long long key, Move move, int depth) {
    int key_count = moveTable.count(key);
    MoveEntry moveEntry = moveTable.get(key);


    if (key_count == 0) {
        // Not found
        moveTable.insert(key, MoveEntry(move, depth));
    }
    else if(depth > moveEntry.depth) {
        moveTable.insert(key, MoveEntry(move, depth));
    }
}


//vector<Move> NegamaxPlayer::searchMoves(State &state, vector<Move>& moves, int depth) {
void NegamaxPlayer::searchMoves(State &state, vector<Move>& moves, int depth) {
    vector<ScoredMove> scoredMoves;
    for(Move &move : moves) {
        scoredMoves.push_back(ScoredMove(move, LONG_MIN));
    }

    long alpha = -11000;
    long beta = 11000;
    long best = LONG_MIN;

    for(ScoredMove &move : scoredMoves) {
        state.makeMove(move.move);
        try {
            move.score = -negamax(state, depth - 1, -beta, -alpha);
        } catch (string e) {
            throw e;
        }
        state.undoMove(move.move);
        if(move.score > best) best = move.score;
        if(best > alpha) alpha = best;
        if(best >= beta) break;
    }

    sort(scoredMoves.begin(), scoredMoves.end());

    moves.clear();
    for(ScoredMove move : scoredMoves) moves.push_back(move.move);
    //return moves;
}

Move NegamaxPlayer::iterativeDeepening(int startDepth, int endDepth) {
    time(&startTime);
    vector<Move> moves = getSortedMoves(state);
    /*
    cout << "Initial get move" << endl;
    for (int i = 0; i < moves.size(); i++) {
        cout << moves[i].row << " " << moves[i].col << endl;
    }
    cout << "Finish" << endl;
    */
    if(moves.size() == 1) return moves[0];
    for(int i = startDepth; i <= endDepth; i++) {
        if (time_out())
            break;
        try {
            //moves = searchMoves(state, moves, i);
            searchMoves(state, moves, i);
        } catch (string e) {
            break;
        }
    }
    return moves[0];
}

Move NegamaxPlayer::getMove(const Gomoku& gameState) {

    // Reset performance counts, clear the hash table
    //totalNodeCount = 0;
    //nonLeafCount = 0;
    //branchesExploredSum = 0;
    moveTable.clear();

    // Create a new internal state object, sync with the game state
    state = State();
    vector<Move> moves = gameState.getMoves();
    for (Move &move: moves) {
        state.makeMove(move);
	}
	/*
	for(int i = 0 ; i < state.board.size() ; i++) {
		for(int j = 0 ; j < state.board[i].size(); j++) {
			cout << (state.board[i][j]) -> index
		}
	}*/ 
    // Run a depth increasing search
    Move best = iterativeDeepening(2, 16);
    //Move best = iterativeDeepening(1, 3);
    return best;
}



bool NegamaxPlayer::time_out() {
    return difftime(time(NULL), startTime) >= max_time;
}
