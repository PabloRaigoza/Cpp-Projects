/*
This program is a command line approach to a the classic game of hangman. Here you can guess letters to form randomly generated words.
NOTE: The part that opens a file and dumps its contents into an array is someone else's code and I DID NOT MAKE IT, and I DO NOT CLAIM IT as my own.
ALSO: I used a word.txt file filled with 10,000 words. This file I found on GitHub and also DID NOT MAKE, and I AM NOT CLAIMING IT.
I will provide the word.txt file that I used on GitHub along with this code.
*/
#include <iostream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{	
	srand((unsigned)time(0));//Used for generating random numbers
	string wordBank[10000];//We make array with 10k variables
	int loop=0;
	string line;

	//I used this code from another person that helps me
	//open a file on my PC and put each line into an array
	ifstream myfile ("words.txt");
	if (myfile.is_open())
	{
		while (! myfile.eof() ) 
		{
			getline (myfile,line); 
			wordBank[loop] = {line};
			loop++;
		}
		myfile.close();
	}
	else cout << "Unable to open file";


	int selector = (rand() % 10001);//Generate random number 1-10000

	string myWord = wordBank[selector];//We random number to find random word
	int myWordLen = myWord.length();//The length of chosen randome word

	char guess;
	char scoreBoard[myWordLen];//Assign board to word length
	char alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	//Make alphabet so user can see which they havn't used
	int counter = 0;//Counter to check if you found word or not

//	cout << selector << ": " << myWord << endl;//If you want to cheat or see word for debugging
//	cout << "Word Length: " << myWord.length() << endl;

	for (int i=0; i<myWordLen; i++){//Creates a board same size as word
		scoreBoard[i] = {'_'};
	}


	cout << "You have " << myWordLen * 2 << " attempts\n" << endl;//Displays number of attempts

	for (int i=0; i<myWordLen * 2; i++)
	{
		for (int omega=0; omega<26; omega++){//Prints alphabet
			if (guess == alpha[omega]){//If a letter has been used, change it to underscore
				alpha[omega] = {'_'};
			}
			cout << alpha[omega];
		}

		cout << endl;

		for (int print=0; print<myWordLen; print++){//Prints board
			cout << scoreBoard[print];
		}

		cout << "\nPick Letter: ";//Prompts user, assigns response to 'guess'
		cin >> guess;

		for (int index=0; index<myWordLen; index++)//Checks entire word for user's letter
		{
			if(guess == myWord[index])
			{
				scoreBoard[index] = guess;
				counter ++;
			}
		}

		if(counter == myWordLen){//If user has entire guessed word, terminate program, and cout they win
			cout << myWord << "\nSuccess!" << endl;
			i = myWordLen * 2;
		}
	}

	if (counter != myWordLen){//If user has lost, cout the word they were looking for and that they have failed
		cout << myWord << "\nYou have failed!\n";
	}

	return 0;
}
