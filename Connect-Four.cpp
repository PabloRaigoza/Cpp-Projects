/*
This program applies a simple take to the classic game of Connect-Four.
This program creates a board (same size as orginal board) and a number under each column.
User selects which column they would like to place, either their X or their O, and a little
animation plays as the peice drops to the bottom most tile possible.
This is all displayed through a terminal console window.
*/
#include <iostream>
#include <unistd.h>
using namespace std;
const int ROWS = 7;
const int COLUMNS = 9;
int player1, player2;
int ground[8] = {ROWS-1,ROWS-1,ROWS-1,ROWS-1,ROWS-1,ROWS-1,ROWS-1,ROWS-1};
void display(char[][COLUMNS]);
void animationX(char[][COLUMNS]);
void animationO(char[][COLUMNS]);

int main(){
	bool gameLoop = true;
	char board[ROWS][COLUMNS];
	for(int i = 0; i < ROWS; i++){
		for(int index = 0; index < COLUMNS; index++){
			if(i == ROWS - 1){
				board[i][index] = '^';
			}
			else if(index == 0 || index == COLUMNS - 1){
				board[i][index] = '|';
			}
			else board[i][index] = ' ';
		}
	}
	display(board);
	while(gameLoop){
		cout << "Player-X: ";
		cin >> player1;
		ground[player1] --;
		animationX(board);
		board[ground[player1]][player1] = 'X';		
		display(board);

		cout << "Player-O: ";
		cin >> player2;
		ground[player2] --;
		animationO(board);
		board[ground[player2]][player2] = 'O';
		display(board);
	}
	return 0;
}

void display(char array[][COLUMNS]){
	system("clear");
	for(int i = 0; i < ROWS; i++){
		for(int index = 0; index < COLUMNS; index++){
			cout << array[i][index];
		}
	cout << endl;
	}

	cout << " ";
	for(int i = 1; i < COLUMNS - 1; i++){
		cout << i;
	}
	cout << endl;
}

void animationX(char array[][COLUMNS]){
	system("clear");
	int counterX = 0;
	for(int loop = 0; loop < ground[player1] + 1; loop++){
		for(int i = 0; i < ROWS; i++){
			for(int index = 0; index < COLUMNS; index++){
				if(player1 == index && counterX == i && counterX < ROWS - 1){
					cout << "X";
				}else cout << array[i][index];
			}
		cout << endl;
		}
	cout << " ";
	for(int i = 1; i < COLUMNS - 1; i++){
		cout << i;
	}
	cout << "\nPlayer-X: \n";
	counterX ++;
	usleep(100000);
	system("clear");
	}
}

void animationO(char array[][COLUMNS]){
	system("clear");
	int counterO = 0;
	for(int loop = 0; loop < ground[player2] + 1; loop++){
		for(int i = 0; i < ROWS; i++){
			for(int index = 0; index < COLUMNS; index++){
				if(player2 == index && counterO == i && counterO < ROWS - 1){
					cout << "O";
				}else cout << array[i][index];
			}
		cout << endl;
		}
	cout << " ";
	for(int i = 1; i < COLUMNS - 1; i++){
		cout << i;
	}
	cout << "\nPlayer-O: \n";
	counterO ++;
	usleep(100000);
	system("clear");
	}
}
