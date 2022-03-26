#include <iostream>
#include "Game.h"

int main() {
	srand(time(NULL));
	int choice;
	Player *p1, *p2;
	std::cout << "Wybierz tryb gry" << std::endl;
	std::cout << "1. PVP" << std::endl;
	std::cout << "2. PVC" << std::endl;
	std::cout << "3. CVC" << std::endl;
	std::cin >> choice;
	if (choice == 1) {
		p1 = new Human();
		p2 = new Human();
	}
	else if (choice == 2) {
		p1 = new Human();
		p2 = new Computer();
	}
	else if (choice == 3) {
		p1 = new Computer();
		p2 = new Computer();
	}
	else {
		std::cout << "Wybrano zly znak, ustawiony zostaje tryb PVC" << std::endl;
		p1 = new Human();
		p2 = new Computer();
	}
	int patrolBoats, destroyers, battleships, carriers;
	std::cout << "Ile statkow dwumasztowych: ";
	std::cin >> patrolBoats;
	std::cout << "Ile statkow trojmasztowych: ";
	std::cin >> destroyers;
	std::cout << "Ile statkow czteromasztowych: ";
	std::cin >> battleships;
	std::cout << "Ile statkow pieciomasztowych: ";
	std::cin >> carriers;
	Board b(patrolBoats, destroyers, battleships, carriers);
	Game g(b, p1, p2);
	g.play();
}