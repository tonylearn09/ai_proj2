
#include <stdlib.h>
#include <stdio.h>
#include "Gomoku.h"
#include "MinimaxPolicy.h"
#include <fstream>


int main(){
     
	FILE *fstate;   /*宣告FILE資料型態的 指標*/ 
  	FILE *fmove;
  	
	Gomoku newGame(1);
	MinimaxPolicy minimaxPolicy(1);
	
	int pre_step = 0;
	int step = 0;
	int move = 0;
	int data[217] = {0};
	int pre_data[217] = {0};
	int onetwo = 0; 	//先手or後手 
	
	map<int, float> weights;
    ifstream weight_file("best.txt");
    if (weight_file.is_open()) {
        for (int key = 0; key < 6; key++) {
            weight_file >> weights[key];
        }
        weight_file.close();
    } else {
        weights = {{0,0.0}, {1,1.0}, {2,2.0}, {3,3.0}, {4,4.0}, {5,5.0}};
    }
    
	while(1) {
		int buffer;
		fstate=fopen("state_13.txt","r");
		if ( fstate == NULL ) { 
			printf("read state error! \n"); 
			continue;
		}
		while (fscanf(fstate, "%d", &buffer) == EOF) {
		 	//printf("%d",buffer);
		  	// when empty file
		}
		
		step = buffer;
		//printf("%d\n", step);
		if (pre_step < step) {
			for(int i = 0 ; i < 217 ; i++) {
		    	//if( i == 0 ) fscanf(fstate , " %d " , &step); //read step
				fscanf(fstate, "%d" , &data[i]); //read board
		 	}
	 		fscanf(fstate, "%d", &onetwo);
	 	
	 		/*for(int i = 0 ; i < 217 ; i++) {
		    	//if( i == 0 ) fscanf(fstate , " %d " , &step); //read step
		    	
				printf( "%d" , data[i]); //read board
	 		}*/
	 		
	 		for (int i = 0 ; i < 217 ; i++) {
	 			if (step == 1) {
	 				move = minimaxPolicy.getNextAction(newGame, weights);
	 				printf("initial\n");
					pre_data[move] = 1;
					data[move] = 1;
					//newGame.print_board();
	 				//system("pause");
					break;
				 } else {
				 	if (pre_data[i] != data[i]) {
				 		//update board
	 					newGame.updateBoard(i);
	 					//printf("oppo : %d\n",i);
	 					//newGame.print_board();
	 					//system("pause");
	 					move = minimaxPolicy.getNextAction(newGame, weights);
	 					pre_data[i] = data[i];
	 					pre_data[move] = 3 - data[i];
	 					break;
					 }
				 }
				 /*
	 			if (pre_data[i] != data[i] && step != 1){
	 				//update board
	 				newGame.updateBoard(i);
	 				printf("oppo : %d\n",i);
	 				newGame.print_board();
	 				system("pause");
	 				move = minimaxPolicy.getNextAction(newGame, weights);
	 				pre_data[i] = data[i];
	 				break;
				}else if(step == 1){
					move = minimaxPolicy.getNextAction(newGame, weights);
					printf("initial\n");
					pre_data[i] = move;
					data[i] = move;
					newGame.print_board();
	 				system("pause");
					break;
				}
				*/
			 }
	 		pre_step = step;
	 		//move step
	 		fmove = fopen("move_13.txt","w"); 
			fprintf (fmove,"%d %d", step, move);
			fclose(fmove);
			newGame.updateBoard(move);
			//printf("move: %d\n",move);
			//newGame.print_board();
			
	 		//system("pause");
			
		} else if (pre_step > step) {
			//clear board
			newGame.clear(1);
			//newGame.print_board();
			//system("pause");
			for(int i = 0 ; i < 127 ; i++) {
				pre_data[i] = 0;
			}
			pre_step = 0;	
		}
		fclose(fstate);
	 	
	 	
	}
	
	
 	
 	
 	
 	
 

	//fprintf(fPtr, " 要寫入的字串 ");   /* 將字串寫入檔案 */

	//fclose(fPtr); /* 關閉檔案 */ 
 
 return 0;   
}
