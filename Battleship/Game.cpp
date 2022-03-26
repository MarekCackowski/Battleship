#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "windows.h" 
#include "Game.h"

Game::Game(Board &b, Player*& p1, Player*& p2) {
	this->isEnded = false;
	this->b = b;
	this->p1 = p1;
	this->p2 = p2;
}
void Game::play() {
	std::cout << "Gracz 1:" << std::endl;
	p1->setBoard(b.visible1);
	std::cout << "Gracz 2:" << std::endl;
	p2->setBoard(b.visible2);
	while (!isEnded) {
		std::cout << "Gracz 1:" << std::endl;
		p1->shoot(b.hidden2, b.visible2);
		std::cout << "Gracz 2:" << std::endl;
		p2->shoot(b.hidden1, b.visible1);
	}
	if (p1->getHits() > p2->getHits())
		std::cout << "Wygral gracz 1" << std::endl;
	else if (p1->getHits() < p2->getHits())
		std::cout << "Wygral gracz 2" << std::endl;
	else
		std::cout << "Remis" << std::endl;
	exit(0);
}

