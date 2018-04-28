#include <iostream>
#include "Gomoku.h"
using namespace std

// function
Gomoku::Gomoku(int first_player) {
    // gomoku board
    init_board();
    get_index_map();
    init_dir_map();
    // reverse_index_map = {v: k for k, v in self.index_map.items()}

    // player 
    // 1 is agent, 2 is opponent
    nextPlayer = first_player;
    lastMove   = make_tuple(-1, -1);
    totalSteps = vector<int>(2); // (agent, opponent)

    // [[agent count], [opponent count]]
    winningCount.push_back(vector<int>(6));
    winningCount.push_back(vector<int>(6));
    winningCount[0][0] = winningCount[1][0] = 217;

    cout << "Finish setting up board" << endl;
}

void Gomoku::init_board() {
    for (int i = 9; i < 18; i++) {
        gomokuboard.push_back(vector<int>(i));
    }
    for (int i = 16; i > 8; i--) {
        gomokuboard.push_back(vector<int>(i));
    }
}

void Gomoku::get_index_map() {
    for (int i = 0; i < 0+9; i++) {
        index_map[i] = make_tuple(0, i);
    }
    for (int i = 9; i < 9+10; i++) {
        index_map[i] = make_tuple(1, i-9);
    }
    for (int i = 19; i < 19+11; i++) {
        index_map[i] = make_tuple(2, i-19);
    }
    for (int i = 30; i < 30+12; i++) {
        index_map[i] = make_tuple(3, i-30);
    }
    for (int i = 42; i < 42+13; i++) {
        index_map[i] = make_tuple(4, i-42);
    }
    for (int i = 55; i < 55+14; i++) {
        index_map[i] = make_tuple(5, i-55);
    }
    for (int i = 69; i < 69+15; i++) {
        index_map[i] = make_tuple(6, i-69);
    }
    for (int i = 84; i < 84+16; i++) {
        index_map[i] = make_tuple(7, i-84);
    }
    for (int i = 100; i < 100+17; i++) {
        index_map[i] = make_tuple(8, i-100);
    }
    for (int i = 117; i < 117+16; i++) {
        index_map[i] = make_tuple(9, i-117);
    }
    for (int i = 133; i < 133+15; i++) {
        index_map[i] = make_tuple(10, i-133);
    }
    for (int i = 148; i < 148+14; i++) {
        index_map[i] = make_tuple(11, i-148);
    }
    for (int i = 162; i < 162+13; i++) {
        index_map[i] = make_tuple(12, i-162);
    }
    for (int i = 175; i < 175+12; i++) {
        index_map[i] = make_tuple(13, i-175);
    }
    for (int i = 187; i < 187+11; i++) {
        index_map[i] = make_tuple(14, i-187);
    }
    for (int i = 198; i < 198+10; i++) {
        index_map[i] = make_tuple(15, i-198);
    }
    for (int i = 208; i < 208+9; i++) {
        index_map[i] = make_tuple(16, i-208);
    }
}

tuple<int, int, int> Gomoku::currentGame() {
    // return the next player, total steps for agent and opponent respectively
    return make_tuple(nextPlayer, totalSteps[0], totalSteps[1]);
}

bool Gomoku::updateBoard(int pos) {
    // update a board given a pos
    // pos is in the form 0~216
    pos_index = index_map[pos];
    pos_index_x = get<0>(pos_index);
    pos_index_y = get<1>(pos_index);
    if (gomokuboard[pos_index_x][pos_index_y] != 0) {
        // no update
        return false;
    }

    totalSteps[nextPlayer - 1] += 1;
    lastMove = pos_index;

    prevWinningCount.push_back(winningCount);
    newWinningCount = updateFeature(pos_index);
    if (nextPlayer == 1) {
        winningCount[0] = newWinningCount["agent"];
        winningCount[1] = newWinningCount["opponent"];
    } else {
        winningCount[0] = newWinningCount["opponent"];
        winningCount[1] = newWinningCount["agent"];
    }
    gomokuboard[pos_index_x][pos_index_y] = nextPlayer;
    nextPlayer = 3 - nextPlayer;

    return True
}

void Gomoku::revert(int lastPos) {
    // revert last move given updated last postion
    pos_index = index_map[lastPos];
    pos_index_x = get<0>(pos_index);
    pos_index_y = get<1>(pos_index);

    totalSteps[2 - self.nextPlayer] -= 1;
    gomokuboard[pos_index_x][pos_index_y] = 0;
    nextPlayer = 3 - nextPlayer;
    lastMove = pos_index;

    winningCount = prevWinningCount.back();
    prevWinningCount.pop_back();
}

int Gomoku::isEnd(bool debug=false) { 
    // check if the game ends
    // return if a game terminates
    // -1 - not end
    // 0 - break even
    // 1 - player 1 wins
    // 2 - player 2 wins

    if (totalSteps[0] + totalSteps[1] >= 217)
        return 0;
    map<string, int> count = {
        {"W", 0}, {"E", 0}, 
        {"NW", 0}, {"SE", 0},
        {"NE", 0}, {"SW", 0}
    }

    lastPlayer = 3 - self.nextPlayer;
    for (auto const& d: count) {
        i = get<0>(lastMove);
        j = get<1>(lastMove);
        while (boardState(i, j) == lastPlayer) {
            count[d.first] += 1;
            if i < 8 {
                // top half
                i += get<0>(is_end_check_dir_map[d.first]);
                j += get<1>(is_end_check_dir_map[d.first]);
            } else {
                i += get<0>(is_end_check_dir_map[d.first+"_b"]);
                j += get<1>(is_end_check_dir_map[d.first+"_b"]);
            }
        }
    }

    if (debug)
        cout << count << endl;
    if ((count["W"] + count["E"] >= 6) ||
            (count["NW"] + count["SE"] >= 6) ||
            (count["NE"] + count["SW"] >= 6)) 
        return lastPlayer;
    else
        return -1;
}

void Gomoku::clear(int first_player) {
    gomokuboard.clear();
    init_board();
    nextPlayer = first_player;
    lastMove = make_tuple(-1, -1);

    totalSteps = vector<int>(2); // (agent, opponent)

    // [[agent count], [opponent count]]
    windowCount[0] = vector<int>(6);
    winningCount[1] = vector<int>(6);
    winningCount[0][0] = winningCount[1][0] = 217;

    prevWinningCount.clear();
    print("Finish clearing up board for restart");
}

map<string, vector<int> > Gomoku::updateFeature(tuple<int, int> pos_index) {
    //print(pos_index);
    windowSize = 5;

    agent = nextPlayer;
    opponent = 3 - agent;

    agentCount = winningCount[agent - 1];
    opponentCount = winningCount[opponent - 1];

    nextMove_i = get<0>(pos_index);
    nextMove_j = get<1>(pos_index);

    set<tuple<int, int> > valid_pos;
    map<string, tuple<int,int> > startPos; 

    // row
    for (int delta = 0; delta < 5; delta++) {
        if (nextMove_j - delta >= 0) {
            valid_tuple = make_tuple(nextMove_i, nextMove_j-delta);
            valid_pos.insert(valid_tuple);
            startPos["row"] = valid_tuple;
        }
    }
    for (int delta = 0; delta < 5; delta++) {
        if (nextMove_j + delta < gomokuboard[nextMove_i].size()) {
            valid_tuple = make_tuple(nextMove_i, nextMove_j+delta);
            valid_pos.insert(valid_tuple);
        }
    }


    if (nextMove_i <= 8) {
        // top half (head)
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i - delta >= 0 && nextMove_j - delta >= 0) {
                valid_tuple = make_tuple(nextMove_i - delta, nextMove_j - delta);
                valid_pos.insert(valid_tuple);
                startPos["diag"] = valid_tuple;
            }
        }
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i - delta >= 0 && nextMove_j < gomokuboard[nextMove_i-delta].size()) {
                valid_tuple = make_tuple(nextMove_i - delta, nextMove_j);
                valid_pos.insert(valid_tuple);
                startPos["rdiag"] = valid_tuple;
            }
        }


        // top half (tail)
        // diag
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i + delta > 8) {
                y_index = nextMove_j + (8 - nextMove_i);
                if (y_index < gomokuboard[nextMove_i+delta].size()) {
                    valid_pos.insert(make_tuple(nextMove_i+delta, y_index));
                }
            } else {
                if (nextMove_j+delta < gomokuboard[nextMove_i+delta].size()) {
                    valid_pos.insert(make_tuple(nextMove_i+delta, nextMove_j+delta));
                }
            }
        }

        // rdiag
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i + delta >= 8) {
                y_index = nextMove_j - (delta - (8 - nextMove_i));
                if (y_index >= 0) {
                    valid_pos.insert(make_tuple(nextMove_i+delta, y_index));
                }
            } else {
                valid_pos.insert(make_tuple(nextMove_i+delta, nextMove_j));
            }
        }

    } else if (nextMove_i > 8) {
        // bottom half (head)
        valid_pos.insert(start_diag_tuple);
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i - delta > 8) {
                valid_tuple = make_tuple(nextMove_i-delta, nextMove_j);
                startPos["diag"] = valid_tuple;
                valid_pos.insert(valid_tuple);
            } else {
                col_index = nextMove_j - (delta - (nextMove_i - 8));
                if (col_index >= 0) {
                    valid_tuple = make_tuple(nextMove_i-delta, col_index)
                    startPos["diag"] = valid_tuple;
                    valid_pos.insert(valid_tuple);
                }
            }
        }

        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i - delta >= 8) {
                if (nextMove_j + delta < gomokuboard[nextMove_i-delta].size()) {
                    valid_tuple = make_tuple(nextMove_i-delta, nextMove_j+delta)
                    startPos["rdiag"] = valid_tuple;
                    valid_pos.insert(valid_tuple)
                }
            } else {
                col_index = nextMove_j + (nextMove_i - 8);
                if (col_index < gomokuboard[nextMove_i-delta].size()) {
                    valid_tuple = make_tuple(nextMove_i-delta, col_index)
                    startPos["rdiag"] = valid_tuple;
                    valid_pos.insert(valid_tuple)
                }
            }
        }

        // bottome half (tail)
        for (int delta = 0; delta < 5; delta++) {
            if (nextMove_i+delta < 17 && nextMove_j < gomokuboard[nextMove_i+delta].size())
                valid_pos.insert(make_tuple(nextMove_i+delta, nextMove_j));
            if (nextMove_i+delta < 17 && nextMove_j-delta >= 0)
                valid_pos.insert(make_tuple(nextMove_i+delta, nextMove_j-delta));
        }
    }
    

    map<int, string> index_dir = {
        {0, "row"}, {1, "diag"}, {2, "rdiag"}
    };
    for (int k = 0; k < 3; k++) {
        pair = startPos[index_dir[k]];
        i = get<0>(pair);
        j = get<1>(pair);
        initial = 0;
        map<string, int> windowCount = {{"agent", 0}, {"opponent", 0}};
        deque<tuple<int, int> > prev_history;
        prev_history.push_back(make_tuple(-1, -1)); //dummy
        prev_history.push_back(make_tuple(i, j));

        while (valid_pos.find(make_tuple(i, j)) != valid_pos.end()) {
            
            if initial < windowSize - 1 {
                if (gomoku.gomokuboard[i][j] == agent)
                    windowCount["agent"] += 1;
                else if (gomoku.gomokuboard[i][j] == opponent)
                    windowCount["opponent"] += 1;
                initial += 1;
                if (i < 8) {
                    // top half
                    i += get<0>(direction[d]);
                    j += get<1>(direction[d]);
                } else {
                    // bottom
                    i += get<0>(direction[d+"_b"]);
                    j += get<1>(direction[d+"_b"]);
                }

                prev_history.push_back(make_tuple(i, j))
                continue
            }


            if (gomoku.gomokuboard[i][j] == agent)
                windowCount["agent"] += 1;
            else if (gomoku.gomokuboard[i][j] == opponent)
                windowCount["opponent"] += 1;


            prev_pair= prev_history.pop_front()
            if (valid_pos.find(prev_pair) != valid_pos.end()) {
                previ = get<0>(prev_pair);
                prevj = get<1>(prev_pair);
                prevLoc = gomokuboard[previ][prevj];
                if (prevLoc == agent)
                    windowCount["agent"] -= 1;
                else if (prevLoc == opponent)
                    windowCount["opponent"] -= 1;
            }

            if (windowCount["opponent"] <= 0) {
                agentCount[windowCount["agent"]] -= 1;
                agentCount[windowCount["agent"] + 1] += 1;
            }
            if (windowCount['agent'] <= 0)
                opponentCount[windowCount["opponent"]] -= 1;

            if i < 8 {
                // top half
                i += get<0>(direction[d]);
                j += get<1>(direction[d]);
            } else {
                // bottom
                i += get<0>(direction[d+"_b"]);
                j += get<1>(direction[d+"_b"]);
            }
            prev_history.push_back(make_tuple(i,j));
        }
    }

    return {{"agent", agentCount}, {"opponent", opponentCount}};
}

int Gomoku::boardState(pos_x, pos_y) { 
    // helper function to return state of a position
    // pos = (coor x, coor y)
    if (pos_x < 0 or pos_x >= 17 or pos_y < 0 or pos_y >= gomokuboard[pos_x].size())
        return -1;
    else:
        return gomokuboard[pos_x][pos_y];
}

void Gomoku::init_dir_map() {
    is_end_check_dir_map = {
        {"W", make_tuple(0, -1)}, {"E", make_tuple(0, 1)}, 
        {"NW", make_tuple(-1, -1)}, {"SE", make_tuple(1, 1)}, 
        {"NE", make_tuple(-1, 0)}, {"SW", make_tuple(1, 0)},
        {"W_b", make_tuple(0, -1)}, {"E_b", make_tuple(0, 1)},
        {"NW_b", make_tuple(-1, 0)}, {"SE_b", make_tuple(1, 0)},
        {"NE_b", make_tuple(-1, 1)}, {"SE_b", make_tuple(1, -1)}
    }
    update_dir_map = {
        {"row", (0, 1)}, {"diag", (1, 1)}, 
        {"rdiag", (1, 0)}, {"row_b", (0, 1)}, 
        {"diag_b", (1, 0)}, {"rdiag_b", (1, -1)}
    }
}
    
