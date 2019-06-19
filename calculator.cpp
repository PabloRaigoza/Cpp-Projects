#include <iostream>
using namespace std;

int main()
{
	//Make all variables for program.
	int number1 = 0, number2 = 0, total = 0, choice = 0, area = 0;

	//Display options for user to select.
	cout << "Add--1  Subtract--2  Multiply--3  Divide--4\n";
	
	//User selects choice.
	cout << "Choice is: ";
	cin >> choice;

	//User selects first number.
	cout << "First Number: ";
	cin >> number1;

	//User selects second number.
	cout << "Second Number: ";
	cin >> number2;

	/*
	Here we run through all possible options for user,
	to select. Then we perform calculations for user.
	*/
	if(choice == 1){
		area = number1 + number2;
		cout << "Sum is: " << area << endl;//Outpouts two added numbers.
	} else if(choice == 2){
		area = number1 - number2;
		cout << "Difference is: " << area << endl;//Outpouts difference of two numbers.
	} else if(choice == 3){
		area = number1 * number2;
		cout << "Product is: " << area << endl;//Outpouts two multiplied numbers.
	} else if(choice == 4){
		area = number1 / number2;
		cout << "Dividend is: " << area << endl;//Outpouts two divided numbers.
	} else {
		cout << "Invalid choice \n";//Produces error in case of invalid answer.
	}

	return 0;
}
