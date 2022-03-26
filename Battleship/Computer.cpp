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

bool Computer::shoot(char hidden[10][10], char visible[10][10]) {
	int x, y, choice = 1;
	while (choice != 0) {
		x = rand() % 10;
		y = rand() % 10;
		if (visible[y - 1][x - 1] > '1' && visible[y - 1][x - 1] < '6') {
			this->hits++;
			std::cout << "Trafiles" << std::endl;
			hidden[y - 1][x - 1] = 'X';
			choice--;
		}
		else if (visible[y - 1][x - 1] == '*') {
			std::cout << "Pudlo" << std::endl;
			hidden[y - 1][x - 1] = 'O';
			choice--;
		}
	}
	showBoard(hidden);
	Sleep(3000);
	if (this->hits == patrolBoats * 2 + destroyers * 3 + battleships * 4 + carriers * 5)
		return true;
	else
		return false;
}

void Computer::setShips(char board[10][10], int howBig, int counter) {
	int x, y, choice;
	char temp[10][10];
	while (counter != 0) {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				temp[i][j] = board[i][j];
		x = rand() % 10;
		y = rand() % 10;
		board[y][x] = static_cast<char>(howBig);
		placeShip(howBig, board, choice);
		if (checkShipPlacement(howBig, board, choice))
			counter--;
		else
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					board[j][i] = temp[j][i];
	}
}

void Computer::setBoard(char board[10][10]) {
	setShips(board, 2, patrolBoats);
	setShips(board, 3, destroyers);
	setShips(board, 4, battleships);
	setShips(board, 5, carriers);
}