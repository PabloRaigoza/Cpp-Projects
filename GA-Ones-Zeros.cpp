/*
Here I am ausing a simple genetic algorythmn to turn an entire
population of ones and zeros into ones.

The concepts I use are:
1. Selection - We select top 2 most fit individuals.
2. One-Point-Crossover - Cross top most fit individuals, and produce child.
3. Mutation - Alow for .1% mutation by listening to parents.
4. Populate - Populate new generation based on our fit individuals and child.
5. Check - Check is we have acheived goal, if not move to next generation.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int INDIVIDUALS = 6;
const int CHROMOSOMES = 14;
void display(int[][CHROMOSOMES]);
void oneD(int[CHROMOSOMES]);
void reload(int [][CHROMOSOMES]);

int main(){
	system("clear");
	srand((unsigned)time(0));
	int OG[INDIVIDUALS][CHROMOSOMES];
	int population[INDIVIDUALS][CHROMOSOMES];
	int parent1[CHROMOSOMES], parent2[CHROMOSOMES];
	int child[CHROMOSOMES];
	int fitness[INDIVIDUALS];
	int fitnessPos[INDIVIDUALS];
	int counter = 0;
	bool loop = true;
	int genCount = 0;
	for(int i = 0; i < INDIVIDUALS; i++){//Populate population
		for(int j = 0; j < CHROMOSOMES; j++){
			population[i][j] = rand() % 2;
			OG[i][j] = population[i][j];
		}
	}

	while(loop == true){
		genCount ++;
		for(int i = 0; i < CHROMOSOMES; i++){
			parent1[i] = 0;
			parent2[i] = 0;
			child[i] = 0;
		}
		for(int j = 0; j < INDIVIDUALS; j++){
			fitness[j] = 0;
			fitnessPos[j] = 0;
		}
		int mostFit = 0, secondFit = 0;
		
		
		int randNum = 0;
		int allFit = 0;
		
		for(int i = 0; i < INDIVIDUALS; i++){//Evaluate fitness
			for(int j = 0; j < CHROMOSOMES; j++){
				fitnessPos[i] = i;
				if(population[i][j] == 1){
					fitness[i]++;
				}
			}
		cout << fitnessPos[i] << ": " << fitness[i] << endl;
		}

		for(int i = 0; i < INDIVIDUALS; i++){//Find first parent
			if(fitness[i] > mostFit){
				mostFit = fitness[i];
				for(int j = 0; j < CHROMOSOMES; j++){
					parent1[j] = population[i][j];
				}
			}
		}
		for(int i = 0; i < INDIVIDUALS; i++){//Find second parent
			if(fitness[i] > secondFit && fitness[i] != mostFit){
				secondFit = fitness[i];
				for(int j = 0; j < CHROMOSOMES; j++){
					parent2[j] = population[i][j];
				}
			}
		}
		
		for(int i = 0; i < INDIVIDUALS; i++){//Count if to see if everyone is fit
			for(int j = 0; j < CHROMOSOMES; j++){
				if(population[i][j] == 1){
					allFit ++;
				}
			}
		}

		if(parent2[0] == 0){//If we could find second most fit, then second most fit must
			secondFit = mostFit;//be ties with the most fit
			for(int i = 0; i < CHROMOSOMES; i++){
				parent2[i] = parent1[i];
			}
		}

		cout << "Fitest: " << mostFit;//Display mostFit, and second most fit
		cout << "\nSecond Fitest: " << secondFit << endl;
		
		cout << "Best parent: ";//display best and seocnd best parent
		oneD(parent1);
		cout << "Second best: ";
		oneD(parent2);
		for(int i = 0; i < CHROMOSOMES; i++){//cross the chromosomes and make child
			if(i >= 0 && i < CHROMOSOMES/2){
				child[i] = parent1[i];
			}
			if(i > (CHROMOSOMES/2)-1 && i < CHROMOSOMES){
				child[i] = parent2[i];
			}
		}
		cout << "Crossed Best parent: ";//display new cromosomes
		oneD(parent1);
		cout << "Crossed Second parent: ";
		oneD(parent2);
		cout << "Child: ";
		oneD(child);
		if(allFit == CHROMOSOMES*INDIVIDUALS){//Checks if everyone is the most fit, if so display
			cout << endl;//poputlation, our child, and stop program
			display(OG);
			display(population);
			cout << "\nGeneration: " << genCount << endl;
			cout << "The Perfect Child!\n";
			oneD(child);
			loop = false;
		}
		for(int i = 0; i < INDIVIDUALS; i++){//Populate population
			for(int j = 0; j < CHROMOSOMES; j++){
				population[i][j] = rand() % 2;
				randNum = rand() % 1000;//we give a 99.9% chance to listen to the parents when populating next egn
				if(parent1[j] != population[i][j] && randNum < 997 || parent2[j] != population[i][j] && randNum < 997){
					population[i][j] = child[i];//but .1% is alotted for mutations
				}
			}
		}
		if(allFit != CHROMOSOMES*INDIVIDUALS){//only display population if all chromosomes are not fit
			reload(population);
		}
		}
	
	return 0;
}

void display(int array[][CHROMOSOMES]){//cycles 2d array, and displays contents
	for(int i = 0; i < INDIVIDUALS; i++){
		for(int j = 0; j < CHROMOSOMES; j++){
			cout << array[i][j];
		}
	cout << endl;
	}
}

void oneD(int array[CHROMOSOMES]){//cycles 1d array, and displays contents
	for(int i = 0; i < CHROMOSOMES; i++){
		cout << array[i];
	}
	cout << endl;
}
void reload(int array[][CHROMOSOMES]){//refreshes screen so terminal is not clogged
	cout << endl;
	system("clear");
	display(array);//also runs display function for its parameter
}
