#include <time.h>
#include<vector>
#include<iostream>
#define SIZE 11
using namespace std;

typedef vector<vector<int>> matrix;
matrix initArray(SIZE, vector<int>(2));
//int totalcount = 0;
int randomstart = 0;
int totalstate = 0;
int length(matrix array) {
	int i = 0;
	while (array[i][0] != -1 && array[i][1] != -1) i++;
	return i;
}

int getRand(int mod) {
	int i;
	i = rand() % mod;
	return i;
}

void printArray(matrix array) {
	for (int i = 0; i < SIZE; i++) {
		cout <<"[" << array[i][0]<<" , "<< array[i][1]<<"] ";
	}
}

int getHeuristic(matrix array) {
	int Heuristic = 0;
	for (int queen = 0; queen<SIZE; queen++) {    //for each queen
		int nextqueen;
		for (nextqueen = queen + 1; nextqueen<SIZE; nextqueen++) {        //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
			if (array[queen][0] == array[nextqueen][0] ||
				array[queen][1] == array[nextqueen][1] || 
				(array[queen][0]- array[queen][1])== (array[nextqueen][0] - array[nextqueen][1]) || 
				(array[queen][0] + array[queen][1]) == (array[nextqueen][0] + array[nextqueen][1])) {   //if conflict
				Heuristic++;
			}
		}
	}
	return Heuristic;
}

void hillClimbing(matrix array) {
	int H = getHeuristic(array);
	if (H == 0) {
		cout<<"\n\nsolution: ";
		printArray(array);
		cout << "\nNumber of random start: " << randomstart;
		cout << "\nNumber of state changes: " << totalstate << endl;
		/*cout<<"count: "<< totalcount <<"\n";*/
		exit(0);
	}
	else {
		matrix nextsquare(SIZE, vector<int>(2));
		nextsquare[0][0] = -1;
		nextsquare[0][1] = -1;

		int nextH = H;
		for (int queen = 0; queen<SIZE; queen++) {                    //for each queen/row        
			int origcol = array[queen][1];                            //save the original column  
			                                                          //searching the whole board
			for (int validcol = 0; validcol<SIZE; validcol++) {       //for each valid column     
				if (validcol != origcol) {                            //not including the current one 
					array[queen][1] = validcol;                       //place the queen in the next column
					totalstate++;
					int newH = getHeuristic(array);                   //get the weight of the modified board
					
					if (newH < nextH) {                               //if it's a better move
						nextsquare[0][0] = queen;
						nextsquare[0][1] = validcol;
						nextsquare[1][0] = -1;
						nextsquare[1][1] = -1;
						nextH = newH;
						//totalcount++;
					
						cout << endl;
						printArray(array);
						cout << " --> Heuristic:  " << nextH;
						hillClimbing(array);
					}
	

				}
			}
			array[queen][1] = origcol;
		}
		//once we're done searching the board
		if (nextsquare[0][0] == -1 && nextsquare[0][1] == -1) {          //if we've found a better move
			
			cout<<"\n\nLocal max reached. Retrying with Random-restart\n";        
			for (int i = 0; i < SIZE; i++) {
				initArray[i][0] = i;
				initArray[i][1] = getRand(SIZE);
			}
			randomstart++;
			printArray(initArray);
			hillClimbing(initArray);
		}
	}
}

int main() {
	srand(time(0)); //seed random

	for (int i = 0; i < SIZE; i++) {
		initArray[i][0] = i;
		initArray[i][1] = getRand(SIZE);
	} 
	cout<<"Running hill climbing with array for size "<<SIZE<<": ";
	printArray(initArray);
	hillClimbing(initArray);
	return 0;
}