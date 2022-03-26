#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Board.h"

Board::Board(int patrolBoats, int destroyers, int battleships, int carriers) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			visible1[i][j] = '*';
			visible2[i][j] = '*';
			hidden1[i][j] = '*';
			hidden2[i][j] = '*';
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

void Board::showBoard(char plansza[10][10]) {
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
			std::cout << plansza[i][j] << "  ";
			if (j == 9)
				std::cout << i + 1;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::placeShip(int howBig, char board[10][10], int choice, int x, int y) {
	int i;
	for (i = 0; i < howBig - 1; i++) {
		switch (choice) {
		case 1:
			if (x > 0) {
				x--;
				board[y][x] = (char)howBig + 48;
			}
			break;
		case 2:
			if (x < 9) {
				x++;
				board[y][x] = (char)howBig + 48;
			}
			break;
		case 3:
			if (y > 0) {
				y--;
				board[y][x] = (char)howBig + 48;
			}
			break;
		case 4:
			if (y < 9) {
				y++;
				board[y][x] = (char)howBig + 48;
			}
			break;
		default:
			if (x > 0) {
				x--;
				board[y][x] = (char)howBig + 48;
			}
			break;
		}
	}
}

bool Board::checkShipPlacement(int howBig, char board[10][10], int choice, int x, int y) {
	int i, j, x, y, y1, y2, lastI, lastJ, howManySquaresPlaced = 0;
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
	for (int i; i < lastI; i++) {
		j = y1;
		lastJ = y2;
		for (int j; j < lastJ; j++) {
			if (board[j][i] == char(howBig) + 48)
				howManySquaresPlaced++;
			if (board[j][i] != char(howBig) + 48 && board[j][i] != '*')
				return false;
		}
	}
	if (howManySquaresPlaced != howBig)
		return false;
	else
		return true;
}
