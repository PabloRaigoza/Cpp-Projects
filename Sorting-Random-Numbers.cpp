//This program generates random numbers, assigns them into an array, displays random array, and sorts and displays new array
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
	srand((unsigned)time(0));

	const int ARRAY_SIZE = 100;//Size of your array
	const unsigned int RANGE = 100;//Your range. DOES NOT include the top number.

	unsigned int randArray[ARRAY_SIZE];//Random array
	unsigned int swap = 0;//Temporaily holds number for swapping

	for(int i=0; i<ARRAY_SIZE; i++){//Create random numbers, puts in array, and displays array
		randArray[i] = {rand() % RANGE};
		cout << randArray[i] << ", ";
	}
	cout << endl;

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
	//cout << endl;
	}

	cout << "----\n";

	for(int i=0; i<ARRAY_SIZE; i++){//Displays the newly fixed array
		cout << randArray[i] << ", ";
	}

	cout << endl;

	return 0;
}
