#include <cstdlib>
#include <string>
#include <random>
#include <iostream>
#include <cstdlib>
#include "../include/State.h"

using namespace std;

State::State() {
    init_board();
    init_neighbor_map();

    generateDirections();

    currentIndex = 1;
    zobristHash = 0;
    init_zobristkeys();

    //cout << "Finish init state" << endl;
}


long long State::getZobristHash() const {
    return zobristHash;
}

void State::makeMove(const Move& move) {
    moveStack.push(move);
    board[move.row][move.col]->index = currentIndex;
    zobristHash ^= zobristKeys[board[move.row][move.col]->index - 1][move.row][move.col];
    //currentIndex = currentIndex == 1 ? 2 : 1;
    currentIndex = 3 - currentIndex;
}

void State::undoMove(const Move& move) {
    moveStack.pop();
    zobristHash ^= zobristKeys[board[move.row][move.col]->index - 1][move.row][move.col];
    board[move.row][move.col]->index = 0;
    //currentIndex = currentIndex == 1 ? 2 : 1;
    currentIndex = 3 - currentIndex;
}

bool State::hasAdjacent(int r, int c, int distance) const {
    for(int i = 0; i < 3; i++) {
        for(int j = 1; j <= distance; j++) {
            if (directions[r][c][i][4 + j]->index == 1
                    || directions[r][c][i][4 - j]->index == 1
                    || directions[r][c][i][4 + j]->index == 2
                    || directions[r][c][i][4 - j]->index == 2) {
                return true;
            }
        }
    }
    return false;
}

void State::generateDirections() {
    directions.resize(board.size());
    for(int r = 0; r < board.size(); r++) {
        directions[r].resize(board[r].size(), FieldV2(3, FieldV1(9)));
        for(int c = 0; c < board[r].size(); c++) {
            directions[r][c][0][4] = board[r][c];
            directions[r][c][1][4] = board[r][c];
            directions[r][c][2][4] = board[r][c];

            vector<string> group1{"NW", "NE", "W"};
            vector<string> group2{"SE", "SW", "E"};

            // Diagonal 1, top left
            // Diagonal 2, top right
            // Horizontal left
            int count = 0;
            int temp_r = r;
            int temp_c = c;
            for (int i = 0; i < group1.size(); ) {
                if (is_valid_cell(temp_r, temp_c)) {
                    directions[r][c][i][4 - count] = board[temp_r][temp_c];
                } else {
                    directions[r][c][i][4 - count] = make_shared<Field>();
                }

                if (count == 4) {
                    // do 4 time
                    i++;
                    count = 0;
                    temp_r = r;
                    temp_c = c;
                    continue;
                }

                if (temp_r <= 8) {
                    temp_r += (neighbor_map[group1[i]]).first;
                    temp_c += (neighbor_map[group1[i]]).second;
                } else {
                    temp_r += (neighbor_map[group1[i]+"_b"]).first;
                    temp_c += (neighbor_map[group1[i]+"_b"]).second;
                }
                count++;

            }

            // Diagonal 1, bottom right
            // Diagonal 2, bottom left
            // Horizontal right
            count = 0;
            temp_r = r;
            temp_c = c;
            for (int i = 0; i < group2.size(); ) {
                if (is_valid_cell(temp_r, temp_c)) {
                    directions[r][c][i][4 + count] = board[temp_r][temp_c];
                } else {
                    directions[r][c][i][4 + count] = make_shared<Field>();
                }

                if (count == 4) {
                    // do 4 time
                    i++;
                    count = 0;
                    temp_r = r;
                    temp_c = c;
                    continue;
                }

                if (temp_r < 8) {
                    temp_r += (neighbor_map[group2[i]]).first;
                    temp_c += (neighbor_map[group2[i]]).second;
                } else {
                    temp_r += (neighbor_map[group2[i]+"_b"]).first;
                    temp_c += (neighbor_map[group2[i]+"_b"]).second;
                }
                count++;

            }

        }
    }

    /*
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            for (int k = 0; k < 3; k++) {
                for (int m = 0; m < 9; m++) {
                    cout << i << " " << j << " " << k << " " << m << endl;
                    cout << "dir["<< i << "][" << j << "][" << k << "][" << m << "] = " << directions[i][j][k][m]->index << endl;
                }
            }
        }
    }
    */
}



void State::init_board() {
    for (int i = 0, limit = 9; i < 17; i++) {
        vector<shared_ptr<Field> > row;
        for (int j = 0; j < limit; j++) {
            row.push_back(make_shared<Field>(i, j));
        }
        board.push_back(row);

        if (i < 8)
            limit = limit + 1;
        else
            limit = limit - 1;
    }
}


void State::init_zobristkeys() {
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator and seed it with entropy.
    uniform_int_distribution<long long> distr;

    for(int i = 0; i < 2; i++) {
        vector<vector<long long> > matrix;
        // 17 rows
        for(int j = 0; j < board.size(); j++) {
            vector<long long> row;
            for(int k = 0; k < board[j].size(); k++) {
                row.push_back(distr(eng));
            }
            matrix.push_back(row);
        }
        zobristKeys.push_back(matrix);
    }
}


int State::getMoves() const {
    return moveStack.size();
}

const Field& State::getField(int r, int c) const {
    return *(board[r][c]);
}

int State::terminal() const {
    Move move = moveStack.top();
    int r = move.row;
    int c = move.col;
    int lastIndex = currentIndex == 1 ? 2 : 1;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            //cout << i << " " << j << endl;
            if(directions[r][c][i][j]->index == lastIndex) {
                int count = 0;
                for(int k = 1; k < 5; k++) {
                    if(directions[r][c][i][j+k]->index == lastIndex) {
                        count++;
                    } else {
                        break;
                    }
                }
                if(count == 4) return lastIndex;
            }
        }
    }
    // 217 is the size of board
    return moveStack.size() == 217 ? 3 : 0;
}

void State::init_neighbor_map() {
    neighbor_map = {
        {"W", make_pair(0, -1)}, {"E", make_pair(0, 1)}, 
        {"NW", make_pair(-1, -1)}, {"SE", make_pair(1, 1)}, 
        {"NE", make_pair(-1, 0)}, {"SW", make_pair(1, 0)},
        {"W_b", make_pair(0, -1)}, {"E_b", make_pair(0, 1)},
        {"NW_b", make_pair(-1, 0)}, {"SE_b", make_pair(1, 0)},
        {"NE_b", make_pair(-1, 1)}, {"SW_b", make_pair(1, -1)}
    };
}

bool State::is_valid_cell(int r, int c) {
    if (r < 0 || r >= board.size() || c < 0 || c >= board[r].size())
        return false;
    else
        return true;
}

void State::printState() const {
    cout << "Current State: " << endl;
    for (int i = 0 ; i < board.size() ; i++) {
        if (i == 0 || i == 16) {
            cout <<  "        " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 1 || i == 15) {
            cout <<  "       " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 2 || i == 14) {
            cout <<  "      " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 3 || i == 13) {
            cout <<  "     " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 4 || i == 12) {
            cout <<  "    " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 5 || i == 11) {
            cout <<  "   " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 6 || i == 10) {
            cout <<  "  " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else if (i == 7 || i == 9) {
            cout <<  " " ;
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        } else {
            for (int j = 0 ; j < board[i].size(); j++) {
                cout << (board[i][j]) -> index << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

}
