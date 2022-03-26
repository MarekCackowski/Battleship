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

void Human::setShips(char board[10][10], int howBig, int counter) {
	int x, y, choice;
	char temp[10][10];
	while (counter != 0) {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				temp[i][j] = board[i][j];
		showBoard(board);
		std::cout << "Wybierz wspolrzedna pozioma i pionowa, w ktorej chcesz zaczac stawiac statek dwumasztowy: ";
		std::cin >> x >> y;
		x--, y--;
		board[y][x] = static_cast<char>(howBig);
		std::cout << std::endl;
		std::cout << "Wybierz w ktora strone chcesz dolozyc pozostale maszty (1- lewo, 2- prawo, 3- gora, 4- dol): ";
		std::cin >> choice;
		placeShip(howBig, board, choice);
		if (checkShipPlacement(howBig, board, choice))
			counter--;
		else {
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					board[j][i] = temp[j][i];
			std::cout << "Statek nieodpowiednio ustawiony sproboj jeszcze raz" << std::endl;
		}
	}
	Sleep(3000);
}

void Human::setBoard(char board[10][10]) {
	setShips(board, 2, patrolBoats);
	setShips(board, 3, destroyers);
	setShips(board, 4, battleships);
	setShips(board, 5, carriers);
}

bool Human::shoot(char hidden[10][10], char visible[10][10]) {
	showBoard(hidden);
	int x, y, choice = 1;
	while (choice != 0) {
		std::cout << "Wybierz wspolrzedna pozioma i pionowa, w ktora chcesz strzelic: ";
		std::cin >> x >> y;
		if (x > 10 || y > 10 || x <= 0 || y <= 0)
			std::cout << "To pole jest poza plansza, wybierz ponownie" << std::endl;
		else if (hidden[y - 1][x - 1] == 'X' || hidden[y - 1][x - 1] == 'O')
			std::cout << "Juz tu strzeliles, wybierz ponownie" << std::endl;
		else if (visible[y - 1][x - 1] != '*') {
			this->hits++;
			std::cout << "Trafiles" << std::endl;
			hidden[y - 1][x - 1] = 'X';
			choice--;
		}
		else {
			std::cout << "Pudlo" << std::endl;
			hidden[y - 1][x - 1] = 'O';
			choice--;
		}
	}
	showBoard(hidden);
	Sleep(1000);
	if (this->hits == patrolBoats * 2 + destroyers * 3 + battleships * 4 + carriers * 5)
		return true;
	else
		return false;
}