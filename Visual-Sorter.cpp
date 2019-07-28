/*
This program provides a simple way to track how a sorter works. Here I use functions and an array to display
my sorter onto a simple terminal console.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;
const int ARRAY_SIZE = 90;
const int RANGE = 50;

int randArray[ARRAY_SIZE];
char board[ARRAY_SIZE][ARRAY_SIZE];
int randNum;
int buffer;


void update();
void displayBoard(char randArray[][ARRAY_SIZE]);



int main(){
	srand((unsigned)time(0));
	system("clear");

//	int randArray[ARRAY_SIZE];
//	char board[ARRAY_SIZE][RANGE];
//	int randNum;
//	int buffer;
	for(int i = 0; i < ARRAY_SIZE; i++){//Populate Array
		randArray[i] = i;
	}

	for(int i = 0; i < ARRAY_SIZE; i++){//Scramble it
		randNum = rand() % ARRAY_SIZE + 1;
		buffer = randArray[i];
		randArray[i] = randArray[randNum];
		randArray[randNum] = buffer;
		buffer = 0;
	}
	
	int swap;
	double counter;
	for(int index = 0; index < ARRAY_SIZE; index++){//Cycles entire list for every single item
		for(int i=0; i<ARRAY_SIZE; i++){//Makes sure that the left is bigger than the right and cyles throughout entire list
			int nextNum = i + 1;
			if (randArray[i] > randArray[nextNum])
			{
				swap = randArray[i];
				randArray[i] = randArray[nextNum];
				randArray[nextNum] = swap;
			}
			
		//cout << randArray[i] << ", ";//Used if you want we want to debug to see any errors
		}
	cout << endl;
	usleep(100000);
	system("clear");
	update();
	displayBoard(board);
	counter += .1;
	cout << counter;
	}






	return 0;
}
void update(){
	for(int i = 0; i < ARRAY_SIZE; i++){
//		cout << randArray[i];
		for(int j = 0; j < randArray[i]; j++){
			board[i][j] = '#';
		}
		for(int index = 0; index < ARRAY_SIZE - randArray[i]; index++){
			board[i][(ARRAY_SIZE - 1) - index] = ' ';
		}
	}
}

void displayBoard(char randArray[][ARRAY_SIZE]){
	for(int j = 0; j < ARRAY_SIZE; j++){
		for(int i = 0; i < ARRAY_SIZE; i++){
			cout << randArray[i][(ARRAY_SIZE - 1) - j];
		}
		cout << endl;
	}
}

