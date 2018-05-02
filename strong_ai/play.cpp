#include <iostream>
#include <ctime>
#include <fstream>
#include "Gomoku.h"
#include "RandomPolicy.h"
#include "NegamaxPlayer.h"
#include "Move.h"

using namespace std;


int main(){
    int iteration = 1;
    vector<int> numberWin(2);
    vector<int> numSteps(2);
    
    for (int i = 0; i < iteration; i++) {
        Gomoku newGame;
        newGame.print_board();
        cout << endl;
        //print "start a new Gomoku game with board size %dx%d"%(boardSize, boardSize)
    
        RandomPolicy randomPolicy;
        NegamaxPlayer negamaxPlayer;
       
        //vector<vector<int> > time_to_move;
        while (newGame.isEnd() < 0) {
            
            int currentIndex = newGame.getCurrentIndex();
            time_t start = time(NULL);
            Move move;
            
            if (currentIndex == 1) {
                //action = minimaxPolicy.getNextAction(newGame);        
                int action = randomPolicy.getNextAction(newGame);
                move = Move(newGame.index_map[action]);
                //action = minimaxPolicy.getNextAction(newGame)
                cout << "player 1 selects (" << move.row << ", " << move.col << ")" << endl;
                cout << "player 1 uses " << difftime(time(NULL), start) << " seconds to select a move" << endl;
                newGame.updateBoard(action);
            } else {
                //cout << "Human turn (position): ";
                //cin >> action;
                move = negamaxPlayer.getMove(newGame);        

                //action = baselinePolicy.getNextAction(newGame)
                cout << "player 2 selects (" << move.row << ", " << move.col << ")" << endl;
                cout << "player 2 uses " << difftime(time(NULL), start) << " seconds to select a move" << endl;
                newGame.updateBoard(move);
            }
            //time_to_move[nextPlayer - 1].append(time.time() - start)
            //print "player %d places on (%d, %d)"%(nextPlayer, action[0], action[1])
            newGame.print_board();
            cout << endl;
            //inp = input('Enter')
            //cout << action << endl;
            //cout << newGame.isEnd() << endl;
            //newGame.print_board();
            //tuple<int,int,int> state = newGame.currentGame();
            //int losePlayer = get<0>(state);
            //int totalStep0 = get<1>(state);
            //int totalStep1 = get<2>(state);
            //cout << totalStep0 + totalStep1 << endl;
            //system("pause");
        }
        //cout << newGame.isEnd() << endl;

        tuple<int,int,int> state = newGame.currentGame();
        int losePlayer = get<0>(state);
        int totalStep0 = get<1>(state);
        int totalStep1 = get<2>(state);
        //losePlayer, totalStep0, totalStep1 = newGame.currentGame()
        int winPlayer = 3 - losePlayer;
        if (newGame.isEnd() != 0) {
            /*
            numberWin[winPlayer-1] += 1;
            if (winPlayer == 1) {
                numSteps[winPlayer-1] = totalStep0;
            } else if(winPlayer == 2) {
                numSteps[winPlayer-1] = totalStep1;
            }
            */
            
            cout << "#### player "<< winPlayer << " wins" << endl;
        } else {
            cout << "break even!" << endl;
        }
        //newGame.print_board();
        //print(newGame.isEnd())
    }
    //system("pause");
    return 0;
}


