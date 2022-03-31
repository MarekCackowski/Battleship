#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "windows.h" 
#include "Game.h"

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

Game::Game(Board &b, Player*& p1, Player*& p2) {
	this->isEnded = false;
	this->b = b;
	this->p1 = p1;
	this->p2 = p2;
}
void Game::play() {
	std::cout << "Player 1:" << std::endl;
	p1->setBoard(0, b);
	clear();
	std::cout << "Player 2:" << std::endl;
	p2->setBoard(1, b);
	clear();
	while (!isEnded) {
		std::cout << "Player 1:" << std::endl;
		isEnded = p1->shoot(1, b);
		clear();
		std::cout << "Player 2:" << std::endl;
		if (!isEnded)
			isEnded= p2->shoot(0, b);
		else
			p2->shoot(0, b);
		clear();
	}
	if (p1->getHits() > p2->getHits())
		std::cout << "Player 1 won" << std::endl;
	else if (p1->getHits() < p2->getHits())
		std::cout << "Player 2 won" << std::endl;
	else
		std::cout << "Tie" << std::endl;
	exit(0);
}

