#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h" 
#include "Human.h"

Human::Human() {
	this->hits = 0;
}

int Human::getHits() {
	return this->hits;
}

void Human::setShips(int whichPlayer, int howBig, int counter, Board& b) {
	int x, y, choice;
	char temp[10][10];
	while (counter != 0) {

		//create temp table in case the placement is incorrect
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				temp[i][j] = b.hidden[whichPlayer][i][j];
		b.showHiddenBoard(whichPlayer);
		std::cout << "Pick coordinates to place ship (horizontal first): ";
		std::cin >> x >> y;
		x--, y--;
		b.hidden[whichPlayer][y][x] = (char)(howBig + '0');
		std::cout << std::endl;
		std::cout << "Pick direction (1- left, 2- right, 3- up, 4- down): ";
		std::cin >> choice;
		b.placeShip(howBig, whichPlayer, choice, x, y);
		if (b.checkShipPlacement(howBig, whichPlayer, choice, x, y))
			counter--;
		else {
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					b.hidden[whichPlayer][j][i] = temp[j][i];
			std::cout << "Incorrect placement, pick again." << std::endl;
		}
	}
}

void Human::setBoard(int whichPlayer, Board& b) {

	//placing every type of ship one by one
	setShips(whichPlayer, 2, b.getPatrolBoats(), b);
	setShips(whichPlayer, 3, b.getDestroyers(), b);
	setShips(whichPlayer, 4, b.getBattleships(), b);
	setShips(whichPlayer, 5, b.getCarriers(), b);
	Sleep(3000);
}

bool Human::shoot(int whichPlayer, Board& b) {
	b.showHiddenBoard(whichPlayer);
	int x, y, choice = 1;

	//going in loop till picked coordinates are correct
	while (choice != 0) {
		std::cout << "Pick coordinates to shoot (horizontal first): ";
		std::cin >> x >> y;
		if (x > 10 || y > 10 || x <= 0 || y <= 0)
			std::cout << "This coordinates are outside the map, pick again" << std::endl;
		else if (b.hidden[whichPlayer][y - 1][x - 1] == 'X' || b.hidden[whichPlayer][y - 1][x - 1] == 'O')
			std::cout << "You already shot here, pick again" << std::endl;
		else if (b.hidden[whichPlayer][y - 1][x - 1] != '*') {
			this->hits++;
			std::cout << "Hit!" << std::endl;
			b.visible[whichPlayer][y - 1][x - 1] = 'X';
			choice--;
		}
		else {
			std::cout << "Miss" << std::endl;
			b.visible[whichPlayer][y - 1][x - 1] = 'O';
			choice--;
		}
	}
	b.showVisibleBoard(whichPlayer);
	Sleep(1000);
	if (this->hits == b.getPatrolBoats() * 2 + b.getDestroyers() * 3 + b.getBattleships() * 4 + b.getCarriers() * 5)
		return true;
	else
		return false;
}