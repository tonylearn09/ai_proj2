#ifndef GOMOKU_H
#define GOMOKU_H
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque> 
#include <stack>
#include <utility>
#include "Move.h"
using namespace std;

class Gomoku {
    public:
        //pair<int, int> lastMove;
        vector<int> totalSteps;
        //vector<vector<int> > winningCount;
        //vector<vector<vector<int> > >  prevWinningCount;

        map<int, pair<int, int> > index_map;
        map<string, pair<int, int> > is_end_check_dir_map;
        //map<string, pair<int, int> > update_dir_map;

        Gomoku();
        void init_board();
        void get_index_map();

        tuple<int, int, int> currentGame();
        bool updateBoard(int pos);
        bool updateBoard(Move move);
        void revert();
        int isEnd();
        void clear();
        int boardState(int pos_x, int pos_y);
        void print_board();

        const vector<Move>& getMoves() const ;
        Move getLastMove();
        int getCurrentIndex();
    private:
        void init_dir_map();

        // data
        vector<Move> moves;
        int currentIndex;
        vector<vector<int> > gomokuboard;

};


#endif
