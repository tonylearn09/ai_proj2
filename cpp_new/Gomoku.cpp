#include <iostream>
#include <fstream>
#include "Gomoku.h"

using namespace std;

// function
Gomoku::Gomoku() {
    // gomoku board
    init_board();
    init_index_map();
    init_reverse_index_map();
    init_dir_map();


    // player 
    // 1 is agent, 2 is opponent
    currentIndex = 1;
    //lastMove   = make_pair(-1, -1);
    totalSteps = vector<int>(2); // (agent, opponent)

    cout << "Finish setting up gameboard" << endl;
}

void Gomoku::init_board() {
    for (int i = 9; i < 18; i++) {
        gomokuboard.push_back(vector<int>(i));
    }
    for (int i = 16; i > 8; i--) {
        gomokuboard.push_back(vector<int>(i));
    }
}

void Gomoku::init_index_map() {
    for (int i = 0; i < 0+9; i++) {
        index_map[i] = Move(0, i);
    }
    for (int i = 9; i < 9+10; i++) {
        index_map[i] = Move(1, i-9);
    }
    for (int i = 19; i < 19+11; i++) {
        index_map[i] = Move(2, i-19);
    }
    for (int i = 30; i < 30+12; i++) {
        index_map[i] = Move(3, i-30);
    }
    for (int i = 42; i < 42+13; i++) {
        index_map[i] = Move(4, i-42);
    }
    for (int i = 55; i < 55+14; i++) {
        index_map[i] = Move(5, i-55);
    }
    for (int i = 69; i < 69+15; i++) {
        index_map[i] = Move(6, i-69);
    }
    for (int i = 84; i < 84+16; i++) {
        index_map[i] = Move(7, i-84);
    }
    for (int i = 100; i < 100+17; i++) {
        index_map[i] = Move(8, i-100);
    }
    for (int i = 117; i < 117+16; i++) {
        index_map[i] = Move(9, i-117);
    }
    for (int i = 133; i < 133+15; i++) {
        index_map[i] = Move(10, i-133);
    }
    for (int i = 148; i < 148+14; i++) {
        index_map[i] = Move(11, i-148);
    }
    for (int i = 162; i < 162+13; i++) {
        index_map[i] = Move(12, i-162);
    }
    for (int i = 175; i < 175+12; i++) {
        index_map[i] = Move(13, i-175);
    }
    for (int i = 187; i < 187+11; i++) {
        index_map[i] = Move(14, i-187);
    }
    for (int i = 198; i < 198+10; i++) {
        index_map[i] = Move(15, i-198);
    }
    for (int i = 208; i < 208+9; i++) {
        index_map[i] = Move(16, i-208);
    }
}

int Gomoku::getCurrentIndex() {
    return currentIndex;
}

const vector<Move>& Gomoku::getMoves() const {
    return moves;
}

Move Gomoku::getLastMove() {
    if (moves.empty())
        return Move(); // default is row=-1, col=-1
    else
        return moves.back();
}

tuple<int, int, int> Gomoku::currentGame() {
    // return the next player, total steps for agent and opponent respectively
    return make_tuple(currentIndex, totalSteps[0], totalSteps[1]);
}

bool Gomoku::updateBoard(int pos) {
    // update a board given a pos
    // pos is in the form 0~216
    //pair<int, int> pos_index = index_map[pos];
    Move pos_index = index_map[pos];
    return updateBoard(pos_index);
}

bool Gomoku::updateBoard(Move move) {
    // update a board given a pos
    // pos is in the form 0~216
    int pos_index_x = move.row;
    int pos_index_y = move.col;
    if (gomokuboard[pos_index_x][pos_index_y] != 0) {
        // no update
        return false;
    }

    moves.push_back(move);
    cout << endl;

    cout << "Vector Elemet: ";
    for (int i = 0; i < moves.size(); i++) {
    	cout << reverse_index_map[ moves[i] ] << " ";
			
	}
	cout << endl;
    totalSteps[currentIndex - 1] += 1;
    //cout << totalSteps[0] << " " << totalSteps[1] << endl;
    //lastMove = pos_index;

    gomokuboard[pos_index_x][pos_index_y] = currentIndex;
    currentIndex = 3 - currentIndex;

    return true;
}

void Gomoku::revert() {
    // revert last move given updated last postion
    //tuple<int, int> pos_index = index_map[lastPos];
    //int pos_index_x = get<0>(pos_index);
    //int pos_index_y = get<1>(pos_index);

    if (moves.empty()) {
        return;
    }
    Move move = moves.back();
    moves.pop_back();
    totalSteps[2 - currentIndex] -= 1;

    gomokuboard[move.row][move.col] = 0;

    currentIndex = 3 - currentIndex;
    //lastMove = lastPos;

    //winningCount = prevWinningCount.back();
    //prevWinningCount.pop_back();
}

int Gomoku::isEnd() { 
    // check if the game ends
    // return if a game terminates
    // -1 - not end
    // 0 - break even
    // 1 - player 1 wins
    // 2 - player 2 wins
	//cout << totalSteps[0]+totalSteps[1] << endl;
    if (moves.size() < 5)
        return -1;

    if ((totalSteps[0] + totalSteps[1]) >= 217)
        return 0;

    map<string, int> count1 = {
        {"W", 0}, {"NW", 0}, {"NE", 0},
    };
    map<string, int> count2 = {
        {"E", 0}, {"SE", 0}, {"SW", 0}
    };

    int lastPlayer = 3 - currentIndex;
    for (auto const& d: count1) {
        //int i = get<0>(lastMove);
        //int j = get<1>(lastMove);
        Move lastMove = getLastMove();
        int i = lastMove.row;
        int j = lastMove.col;
        while (boardState(i, j) == lastPlayer) {
            count1[d.first] += 1;
            if (i <= 8) {
                // top half
                i += is_end_check_dir_map[d.first].row;
                j += is_end_check_dir_map[d.first].col;
            } else {
                i += is_end_check_dir_map[d.first+"_b"].row;
                j += is_end_check_dir_map[d.first+"_b"].col;
            }
        }
    }
    for (auto const& d: count2) {
        //int i = get<0>(lastMove);
        //int j = get<1>(lastMove);
        Move lastMove = getLastMove();
        int i = lastMove.row;
        int j = lastMove.col;
        while (boardState(i, j) == lastPlayer) {
            count2[d.first] += 1;
            if (i < 8) {
                // top half
                i += is_end_check_dir_map[d.first].row;
                j += is_end_check_dir_map[d.first].col;
            } else {
                i += is_end_check_dir_map[d.first+"_b"].row;
                j += is_end_check_dir_map[d.first+"_b"].col;
            }
        }
    }

    //if (debug)
        //cout << count << endl;
    if ((count1["W"] + count2["E"] >= 6) ||
            (count1["NW"] + count2["SE"] >= 6) ||
            (count1["NE"] + count2["SW"] >= 6)) 
        return lastPlayer;
    else
        return -1;
}

void Gomoku::clear() {
    moves.clear();
    gomokuboard.clear();
    init_board();
    currentIndex = 1;
    //lastMove = make_tuple(-1, -1);

    totalSteps = vector<int>(2); // (agent, opponent)

    // [[agent count], [opponent count]]
    /*
    winningCount[0] = vector<int>(6);
    winningCount[1] = vector<int>(6);
    winningCount[0][0] = winningCount[1][0] = 217;

    prevWinningCount.clear();
    */
    system("pause");
    cout << "Finish clearing up board for restart" << endl ;
}


void Gomoku::print_board() {
    for (int i = 0 ; i < 17 ; i++) {
    	if (i == 0 || i == 16) {
    		cout <<  "        " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 1 || i == 15) {
			cout <<  "       " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 2 || i == 14) {
			cout <<  "      " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 3 || i == 13) {
			cout <<  "     " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 4 || i == 12) {
			cout <<  "    " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 5 || i == 11) {
			cout <<  "   " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 6 || i == 10) {
			cout <<  "  " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else if (i == 7 || i == 9) {
			cout <<  " " ;
    		for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		} else {
			for (int j = 0 ; j < gomokuboard[i].size(); j++) {
    			cout << gomokuboard[i][j] << " ";
			}
			cout << endl;
		}
	}
        
}

int Gomoku::boardState(int pos_x, int pos_y) { 
    // helper function to return state of a position
    // pos = (coor x, coor y)
    if (pos_x < 0 || pos_x >= 17 || pos_y < 0 || pos_y >= gomokuboard[pos_x].size())
        return -1;
    else
        return gomokuboard[pos_x][pos_y];
}


void Gomoku::init_dir_map() {
    is_end_check_dir_map = {
        {"W", Move(0, -1)}, {"E", Move(0, 1)}, 
        {"NW", Move(-1, -1)}, {"SE", Move(1, 1)}, 
        {"NE", Move(-1, 0)}, {"SW", Move(1, 0)},
        {"W_b", Move(0, -1)}, {"E_b", Move(0, 1)},
        {"NW_b", Move(-1, 0)}, {"SE_b", Move(1, 0)},
        {"NE_b", Move(-1, 1)}, {"SW_b", Move(1, -1)}
    };
    /*
    update_dir_map = {
        {"row", make_tuple(0, 1)}, {"diag", make_tuple(1, 1)}, 
        {"rdiag", make_tuple(1, 0)}, {"row_b", make_tuple(0, 1)}, 
        {"diag_b", make_tuple(1, 0)}, {"rdiag_b", make_tuple(1, -1)}
    };
    */
}

void Gomoku::init_reverse_index_map() {
    for (unordered_map<int, Move>::iterator i = index_map.begin(); i != index_map.end(); ++i)
        reverse_index_map[i->second] = i->first;

    /*
    for (auto &x: reverse_index_map) {
        if (x.first == index_map[x.second]) {
            cout << "Great" << endl;
        } else {
            cerr << "Error" << endl;
        }
    }
    */
}

/*
int main(){
	
	Gomoku g(1);
	g.updateBoard(79);
	g.updateBoard(84);
	g.updateBoard(80);
	g.updateBoard(86);
	g.updateBoard(81);
	g.updateBoard(85);
	g.updateBoard(82);
	g.updateBoard(87);
	g.updateBoard(100);
	g.updateBoard(88);
	cout << g.isEnd() << endl;
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 6 ; j++)
			cout << g.winningCount[i][j] << " ";
		cout << endl;
	}
	g.print_board();
}
*/
