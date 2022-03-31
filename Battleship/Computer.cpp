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

bool Computer::hitOrMiss(int whichPlayer, Board& b, int x, int y) {
	if (b.hidden[whichPlayer][y][x] > '1' && b.hidden[whichPlayer][y][x] < '6') {
		this->hits++;
		std::cout << "Hit!" << std::endl;
		b.visible[whichPlayer][y][x] = 'X';
		return true;
	}
	else if (b.visible[whichPlayer][y][x] == '*') {
		std::cout << "Miss" << std::endl;
		b.visible[whichPlayer][y][x] = 'O';
		return true;
	}
	return false;
}

bool Computer::shoot(int whichPlayer, Board& b) {
	int counter;
	bool turnEnd = false;
	
	//checking horizontally if there is an uninterrupted series of hits
	int i = 0, j = 0, x = -10, y = -10;
	while (i < 10 && !turnEnd) {
		counter = 0;
		while (j < 10 && !turnEnd) {
			if (b.visible[whichPlayer][i][j] == 'X') {
				y = i;
				x = j;
				counter++;
			}
			if (counter > 0 && (b.visible[whichPlayer][i][j] != 'X' || j == 9)) {

				//if the number of hits in series is equal to 1 it is checked if lower and upper spot is not X
				if (x - 1 >= 0 && counter == 1 && b.visible[whichPlayer][y][x - 1] == '*' && (y - 1 <= 0 || b.visible[whichPlayer][y - 1][x] != 'X')
					&& (y + 1 > 10 || b.visible[whichPlayer][y + 1][x] != 'X') && !turnEnd) {

					turnEnd = this->hitOrMiss(whichPlayer, b, x - 1, y);
				}
				if (x + 1 < 10 && counter == 1 && b.visible[whichPlayer][y][x + 1] == '*' && (y - 1 <= 0 || b.visible[whichPlayer][y - 1][x] != 'X')
					&& (y + 1 > 10 || b.visible[whichPlayer][y + 1][x] != 'X') && !turnEnd) {

					turnEnd = this->hitOrMiss(whichPlayer, b, x + 1, y);
				}

				if (counter > 1 && counter < 5 && !turnEnd) {
					if (x - counter >= 0 && b.visible[whichPlayer][y][x - counter] == '*') {
						turnEnd = this->hitOrMiss(whichPlayer, b, x - counter, y);
					}
					if (x + 1 < 10 && b.visible[whichPlayer][y][x + 1] == '*' && !turnEnd) {
						turnEnd = this->hitOrMiss(whichPlayer, b, x + 1, y);
					}
				}
				counter = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}

	//checking vertically if there is an uninterrupted series of hits
	i = 0, j = 0, x = -10, y = -10;
	while (i < 10 && !turnEnd) {
		counter = 0;
		while (j < 10 && !turnEnd) {
			if (b.visible[whichPlayer][j][i] == 'X') {
				y = j;
				x = i;
				counter++;
			}
			if (counter > 0 && (b.visible[whichPlayer][j][i] != 'X' || j == 9)) {

				//if the number of hits in series is equal to 1 it is checked if left and right spot is not X
				if (y - 1 >= 0 && counter == 1 && b.visible[whichPlayer][x][y - 1] == '*' && (x - 1 <= 0 || b.visible[whichPlayer][x - 1][y] != 'X')
					&& (x + 1 > 10 || b.visible[whichPlayer][x + 1][y] != 'X') && !turnEnd) {

					turnEnd = this->hitOrMiss(whichPlayer, b, x, y - 1);
				}
				if (y + 1 < 10 && counter == 1 && b.visible[whichPlayer][x][y + 1] == '*' && (x - 1 <= 0 || b.visible[whichPlayer][x - 1][y] != 'X')
					&& (x + 1 > 10 || b.visible[whichPlayer][x + 1][y] != 'X') && !turnEnd) {

					turnEnd = this->hitOrMiss(whichPlayer, b, x, y + 1);
				}

				if (counter > 1 && counter < 5 && !turnEnd) {
					if (y - counter >= 0 && b.visible[whichPlayer][x][y - counter] == '*') {
						turnEnd = this->hitOrMiss(whichPlayer, b, x, y - counter);
					}
					if (y + 1 < 10 && b.visible[whichPlayer][x][y + 1] == '*' && !turnEnd) {
						turnEnd = this->hitOrMiss(whichPlayer, b, x, y + 1);
					}
				}
				counter = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}

	//if no uninterrupted series was found picking random coordinates in loop till picked coordinates are correct
	while (!turnEnd) {
		x = rand() % 10;
		y = rand() % 10;
		turnEnd = this->hitOrMiss(whichPlayer, b, x, y);
	}
	b.showVisibleBoard(whichPlayer);
	Sleep(3000);
	if (this->hits == b.getPatrolBoats() * 2 + b.getDestroyers() * 3 + b.getBattleships() * 4 + b.getCarriers() * 5)
		return true;
	else
		return false;
}