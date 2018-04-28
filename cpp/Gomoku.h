#ifndef GOMOKU_H
#define GOMOKU_H
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Gomoku {
    public:
        // data
        int nextPlayer;
        tuple<int, int> lastMove;
        vector<int> totalSteps;
        vector<vector<int> > winningCount;
        vector<vector<vector<int> > >  prevWinningCount;
        vector<vector<int> > gomokuboard;
        map<int, tuple<int, int> > index_map;
        map<string, tuple<int, int> > is_end_check_dir_map;
        map<string, tuple<int, int> > update_dir_map;

        Gomoku(int first_player);
        void init_board();
        void get_index_map();
        tuple<int, int, int> currentGame();
        bool updateBoard(int pos);
        void revert(int lastPos);
        int isEnd(bool debug=false);
        void clear(int first_player);
        map<string, vector<int> > updateFeature(tuple<int, int> pos_index);
    private:
        int boardState(pos_x, pos_y);
        void init_dir_map();

};


#endif
