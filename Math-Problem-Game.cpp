//This program generates random math equations for you to answer. These questions are fairly
//easy, as they are intended for my 8yr old little sister. But by increasing the range of the random numbers
//it makes the problems a lot harder.
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace  std;
int main(){
	//Here we make all our variables
	srand((unsigned)time(0)); //This is our random numbers
	int GAME_CLOCK = true; //Dictates whether we play or not
	int num1 = rand() % 11 + 10;//Generate number between 10-20
	int num2 = rand() % 11;//Generate number 0-10
	int operation = rand() % 3 + 1;//Dictates our operation
	int answer = 0;//True answer to problem
	int guess = 0;//User's answer
	int oldNum1 = 0;//Last random number is stored here
	int oldNum2 = 0;
	int multSimpler = num1 - 10;//Helps make multiplication easier
	int scoreBoard = 0;//Stores how many answer user got right

	while (GAME_CLOCK == true){//Game loop that keep game running
		srand((unsigned)time(0));

		/*This loop generates fresh numbers that are not the same as the old numbers
		and numbers that are not 0s.
		*/
		while (oldNum1 == num1 || oldNum2 == num2 || num1 == 0 || num2 == 0){
			num1 = rand() % 11 + 10;//Generate two random numbers. The first is bigger so we don't get negatives
			num2 = rand() % 11;
			operation = rand() % 3 + 1;//Generate operator
			//cout << "Repeated\n"; //Alows for debuggin repeated number. This is becuase my numbers are not random.
		}
		oldNum1 = num1;//Store past numbers
		oldNum2 = num2;
		multSimpler = num1 - 10;//Bring the first number down by 10 to make multiplication easier



		/*Here we check our operation value so we can provide a
		math problem. 1 = Addition, 2 = Subtraction, and 3 = multiplication
		*/
		if (operation == 1){
			cout << num1 << " + " << num2 << " = ";//Generates equation
			cin >> guess;//Prompt user, assigns response to guess vairable
			answer = num1 + num2;//Computer finds out answer
		} else if (operation == 2){//Does same with addition, but with the subtraction operator
			cout << num1 << " - " << num2 << " = ";
			cin >> guess;
			answer = num1 - num2;
		} else if(operation == 3) {
			cout << multSimpler << " x " << num2 << " = ";//Here we use our 'multSimpler' vairable to make problem easier
			cin >> guess;
			answer = multSimpler * num2;
		} else {//Stops game if operation is not 1, 2, or 3
			GAME_CLOCK = false;
		}

		if (guess != answer) {//If user is wrong, display true answer, display their score, stops game
			cout << endl << "Answer: " << answer;
			cout << "\nScore: " << scoreBoard << endl;
			GAME_CLOCK = false;
		} else {
			scoreBoard = scoreBoard + 1;//add one to user's score
		}

		num1 = 0;//Reset numbers for next problem
		num2 = 0;
		guess = 0;
		answer = 0;
	}
	return 0;
}	
