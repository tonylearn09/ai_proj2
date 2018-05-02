#ifndef GOMOKU_H
#define GOMOKU_H
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <deque> 
#include <stack>
#include <utility>
#include "Move.h"

class Gomoku {
    public:
        //pair<int, int> lastMove;
        std::vector<int> totalSteps;
        //vector<vector<int> > winningCount;
        //vector<vector<vector<int> > >  prevWinningCount;

        std::unordered_map<int, Move> index_map;
        std::unordered_map<Move, int> reverse_index_map;
        std::map<std::string, Move> is_end_check_dir_map;
        //map<string, pair<int, int> > update_dir_map;

        Gomoku();

        std::tuple<int, int, int> currentGame();
        bool updateBoard(int pos);
        bool updateBoard(Move move);
        void revert();
        int isEnd();
        void clear();
        int boardState(int pos_x, int pos_y);
        void print_board();

        const std::vector<Move>& getMoves() const ;
        Move getLastMove();
        int getCurrentIndex();
    private:
        void init_dir_map();
        void init_board();
        void init_index_map();
        void init_reverse_index_map();

        // data
        std::vector<Move> moves;
        int currentIndex;
        std::vector<std::vector<int> > gomokuboard;

};


#endif
