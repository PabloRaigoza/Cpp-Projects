#include <iostream>//Standart library
#include <cstdlib>//Used for random fire spawner
#include <ctime>
using namespace std;

const int ROWS = 4;//Rows and Columns of Forest
const int COLUMNS = 4;

const char FIRE = 'X';//What fire looks like
const char TREE = 'O';//What trees look like
const int BUBBLE = 2;//Bubble around Forest so fire can spread around Forest

void display(char[][COLUMNS + 2]);//Declare display function
int main(){
	bool simClock = true;//Dictates the looping of game
	srand((unsigned)time(0));//Random number generator
	int randomRow = rand() % ROWS + 1;//Random row and column inside forest
	int randomColumn = rand() % COLUMNS + 1;

	char forest[ROWS + BUBBLE][COLUMNS + BUBBLE];//Forest that gets changed and displayed
	char forestCheck[ROWS + BUBBLE][COLUMNS + BUBBLE];//Forest that computer checks

	for(int i = 0; i < ROWS + BUBBLE; i++){//Fill arrays with trees
		for(int index = 0; index < COLUMNS + BUBBLE; index++){
			forest[i][index] = TREE;
			forestCheck[i][index] = TREE; 
		}
	}

	forest[randomRow][randomColumn] = FIRE;//Plant one fire using random numbers
	forestCheck[randomRow][randomColumn] = FIRE;

	int up = 0;//Store values above, below, left, and right of fire
	int down = 0;
	int left = 0;
	int right = 0;
	int counter[2] = {0,0};//Stores gen cycles and whether or not entire forest is burned

	while(simClock == true){//GameClock
		for(int i = 1; i < ROWS + 1; i++){//Cycles for number of rows
			for(int index = 1; index < COLUMNS + 1; index ++){//Cycles number of columns
				up = i - 1;//Up, down, right, and left values are found
				down = i + 1;
				left  = index - 1;
				right  = index + 1;
				if(forestCheck[i][index] == FIRE){//Checks for fire, if so make surrounding tree burned
					forest[up][index] = FIRE;
					forest[down][index] = FIRE;
					forest[i][left] = FIRE;
					forest[i][right] = FIRE;
				}
			}
		}
		for(int i = 1; i < ROWS + 1; i++){//Updates checked forest to new forest
			for(int index = 1; index < COLUMNS + 1; index++){
				forestCheck[i][index] = forest[i][index];
				if(forestCheck[i][index] == FIRE){//Add one to counter fore every fire
					counter[0] ++;
				}
			} 
		}
	if(counter[0] == (ROWS * COLUMNS)){//Checks if counter is equal to number of spaces
		simClock = false;//If so, shutdown simulation
	}else {counter[0] = 0;}//If not, reset counter value

	counter[1] ++;//Add one to generation cycle
	cout << "Generation: " << counter[1] << endl;//Display current generation
	display(forest);//Display current state of forest
	}
	return 0;
}

void display(char array[][COLUMNS + BUBBLE])//Displays forest
{
	for(int i = 1; i < ROWS + 1; i++){//Cylces through every space and displays that space
		for(int index = 1; index < COLUMNS + 1; index++){
			cout << array[i][index] << "  ";
		}
	cout << endl;
	}
}
