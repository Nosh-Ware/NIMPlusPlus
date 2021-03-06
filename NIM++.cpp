// NIM++.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

long startTotal = 0;
long Total = 0;
long subtractMax = 0;
long pastTotal = 0;
long tempInput = 0;
bool playersTurn = false;

//utility
bool random_bool() {
	srand(time(NULL));
	if (rand() % 2 == 1){
		return true;
	}
	else {
		return false;
	}
}

long robotMove() {
	if (subtractMax == Total) { // instant win
		return Total;
	}
	if (Total % subtractMax != 0) { // try to make the number ealy factored by the subrtractive max, the calsic NIM logic
		return Total % subtractMax;
	}
	if (subtractMax <= 2) { // if you cant subtract more then 2, you can se these advanced teqniques
		return 1;
	}
	if (Total > subtractMax*2) { // if the number would be unafrcted by any endgame stratiges
		if (random_bool && (pastTotal - Total) > 0) { // a 50 / 50 chance, and only if the later is a invalidvalid move
			return pastTotal - Total; // return last player move, adds a dynamic ai feel, and allows for more interesting wins
		}
		else {
			return subtractMax; // just try to chop down the number asap
		}
	}
	if (Total % 2 == 1) { // if the total is odd, keep it that way, it makes it harder on the player
		if (subtractMax % 2 == 1) {
			return subtractMax;
		}
		else {
			return subtractMax - 1;
		}
	}
	else { // if the total is even, make it odd, it makes it harder on the player
		if (subtractMax % 2 != 1) {
			return subtractMax;
		}
		else {
			return subtractMax - 1;
		}
	}
}

long playerMove() {
	cin >> tempInput;
	while (tempInput > subtractMax || tempInput <= 0) {
		cout << "Thats not a valid number to subtract, try something else..." << endl;
		cin >> tempInput;
	}
	return tempInput;
}

void setup() {
	if (Total == 0) {
		cout << "Enter the total we wil start with" << endl;
		cin >> Total;
	}
	while (Total <= 1) {
		cout << "The start total cannot be smaller than 1" << endl;
		cout << "Enter a new value" << endl;
		cin >> Total;
	}
	startTotal = Total;

	if (subtractMax == 0) {
		cout << "Enter the highest amount you will be able to subtract from the total" << endl;
		cin >> subtractMax;
	}
	while (subtractMax >= Total) {
		cout << "The highest possible amount cannot be larger than the total" << endl;
		cout << "Enter a new value" << endl;
		cin >> subtractMax;
		while (subtractMax <= 0) {
			cout << "The highest possible amount cannot be smaller than 0" << endl;
			cout << "Enter a new value" << endl;
			cin >> subtractMax;
		}
	}
	while (subtractMax <= 0) {
		cout << "The highest possible amount cannot be smaller than 0" << endl;
		cout << "Enter a new value" << endl;
		cin >> subtractMax;
	}

	cout << "We will start with " << Total << " and subtract with values up to " << subtractMax << endl;
	
	if (random_bool()) { //a aproximate 50/50 chance

		playersTurn = false;
		cout << "I'll start this time" << endl;
	}
	else {
		playersTurn = true;
		cout << "You should start" << endl;
	}
}

int main() {
	setup();
	
	while (Total > 0) {
		pastTotal = Total;

		if (playersTurn) {
			tempInput = playerMove();

			cout << endl << "Your turn: " << Total << " - " << tempInput << " = ";
			Total -= tempInput;
			cout << Total << endl;

			playersTurn = false;
		}
		else {
			tempInput = robotMove();

			cout << "Here I go: " << Total << " - " << tempInput << " = ";
			Total -= tempInput;
			cout << Total << endl;

			playersTurn = true;
		}

	}

	if (!playersTurn) {
		cout << "Congradulations! You Won!" << endl << "See you next time!" << endl;
	}
	else {
		cout << "I Win! Better Luck Next Time!" << endl;
	}
}