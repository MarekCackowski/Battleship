#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h" 
#include "Computer.h"

Computer::Computer() {
	this->hits = 0;
}

int Computer::getHits() {
	return this->hits;
}

void Computer::setShips(int whichPlayer, int howBig, int counter, Board& b) {
	int x, y, choice;
	char temp[10][10];

	//create temp table in case the placement is incorrect
	while (counter != 0) {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				temp[i][j] = b.hidden[whichPlayer][i][j];
		x = rand() % 10;
		y = rand() % 10;
		choice = rand() % 4 + 1;
		b.hidden[whichPlayer][y][x] = (char)(howBig + '0');
		b.placeShip(howBig, whichPlayer, choice, x, y);
		if (b.checkShipPlacement(howBig, whichPlayer, choice, x, y))
			counter--;
		else
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					b.hidden[whichPlayer][j][i] = temp[j][i];
	}
}

void Computer::setBoard(int whichPlayer, Board& b) {

	//placing every type of ship one by one
	setShips(whichPlayer, 2, b.getPatrolBoats(), b);
	setShips(whichPlayer, 3, b.getDestroyers(), b);
	setShips(whichPlayer, 4, b.getBattleships(), b);
	setShips(whichPlayer, 5, b.getCarriers(), b);
}
bool Computer::shoot(int whichPlayer, Board& b) {
	int x, y, choice = 1;

	//going in loop till picked coordinates are correct
	while (choice != 0) {
		x = rand() % 10;
		y = rand() % 10;
		if (b.hidden[whichPlayer][y - 1][x - 1] > '1' && b.hidden[whichPlayer][y - 1][x - 1] < '6') {
			this->hits++;
			std::cout << "Hit!" << std::endl;
			b.visible[whichPlayer][y - 1][x - 1] = 'X';
			choice--;
		}
		else if (b.visible[whichPlayer][y - 1][x - 1] == '*') {
			std::cout << "Miss" << std::endl;
			b.visible[whichPlayer][y - 1][x - 1] = 'O';
			choice--;
		}
	}
	b.showVisibleBoard(whichPlayer);
	Sleep(3000);
	if (this->hits == b.getPatrolBoats() * 2 + b.getDestroyers() * 3 + b.getBattleships() * 4 + b.getCarriers() * 5)
		return true;
	else
		return false;
}