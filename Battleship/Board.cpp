#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Board.h"

Board::Board(int patrolBoats, int destroyers, int battleships, int carriers) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			visible[0][i][j] = '*';
			visible[1][i][j] = '*';
			hidden[0][i][j] = '*';
			hidden[1][i][j] = '*';
		}
	}
	this->patrolBoats = patrolBoats;
	this->destroyers = destroyers;
	this->battleships = battleships;
	this->carriers = carriers;
}
int Board::getPatrolBoats() {
	return this->patrolBoats;
}
int Board::getDestroyers() {
	return this->destroyers;
}
int Board::getBattleships() {
	return this->battleships;
}
int Board::getCarriers() {
	return this->carriers;
}

void Board::showVisibleBoard(int whichPlayer) {
	for (int i = 0; i < 10; i++) {
		std::cout << i + 1;
		if (i < 9)
			std::cout << "  ";
		else
			std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << this->visible[whichPlayer][i][j] << "  ";
			if (j == 9)
				std::cout << i + 1;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::showHiddenBoard(int whichPlayer) {
	for (int i = 0; i < 10; i++) {
		std::cout << i + 1;
		if (i < 9)
			std::cout << "  ";
		else
			std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << this->hidden[whichPlayer][i][j] << "  ";
			if (j == 9)
				std::cout << i + 1;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::placeShip(int howBig, int whichPlayer, int choice, int& x, int& y) {
	int i;
	
	//first square is already placed, remaining are placed in given direction
	for (i = 0; i < howBig - 1; i++) {
		switch (choice) {
		case 1:
			if (x > 0) {
				x--;
				this->hidden[whichPlayer][y][x] = (char)(howBig + '0');
			}
			break;
		case 2:
			if (x < 9) {
				x++;
				this->hidden[whichPlayer][y][x] = (char)(howBig + '0');
			}
			break;
		case 3:
			if (y > 0) {
				y--;
				this->hidden[whichPlayer][y][x] = (char)(howBig + '0');
			}
			break;
		case 4:
			if (y < 9) {
				y++;
				this->hidden[whichPlayer][y][x] = (char)(howBig + '0');
			}
			break;
		default:
			if (x > 0) {
				x--;
				this->hidden[whichPlayer][y][x] = (char)(howBig + '0');
			}
			break;
		}
	}
}

bool Board::checkShipPlacement(int howBig, int whichPlayer, int choice, int x, int y) {
	int i, j, y1, y2, lastI, lastJ, howManySquaresPlaced = 0;
	
	//delimiting the area that may not be correct
	switch (choice) {
	case 1:
		i = x - 1, y1 = y - 1;
		lastI = x + howBig + 1, y2 = y + 2;
		break;
	case 2:
		i = x - howBig, y1 = y - 1;
		lastI = x + 2, y2 = y + 2;
		break;
	case 3:
		i = x - 1, y1 = y - 1;
		lastI = x + 2, y2 = y + howBig + 1;
		break;
	case 4:
		i = x - 1, y1 = y - howBig;
		lastI = x + 2, y2 = y + 2;
		break;
	default:
		i = x - 1, y1 = y - 1;
		lastI = x + howBig + 1, y2 = y + 2;
		break;
	}
	if (i < 0)
		i = 0;
	if (lastI > 10)
		lastI = 10;
	if (y1 < 0)
		y1 = 0;
	if (y2 > 10)
		y2 = 10;

	//checking if there is right number of squares taken by a ship and there are no other ships
	for (i; i < lastI; i++) {
		j = y1;
		lastJ = y2;
		for (j; j < lastJ; j++) {
			if (this->hidden[whichPlayer][j][i] == (char)(howBig + '0'))
				howManySquaresPlaced++;
			if (this->hidden[whichPlayer][j][i] != (char)(howBig + '0') && this->hidden[whichPlayer][j][i] != '*')
				return false;
		}
	}
	if (howManySquaresPlaced != howBig)
		return false;
	else
		return true;
}
