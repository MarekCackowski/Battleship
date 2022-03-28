#include <iostream>
#include "Game.h"

int main() {
	srand(time(NULL));
	int choice;
	Player *p1, *p2;
	std::cout << "Choose game mode: " << std::endl;
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
		std::cout << "Wrong choice. Starting PVE" << std::endl;
		p1 = new Human();
		p2 = new Computer();
	}
	int patrolBoats, destroyers, battleships, carriers;
	std::cout << "How many patrol boats: ";
	std::cin >> patrolBoats;
	std::cout << "How many destroyers: ";
	std::cin >> destroyers;
	std::cout << "How many battleships: ";
	std::cin >> battleships;
	std::cout << "How many carriers: ";
	std::cin >> carriers;
	Board b(patrolBoats, destroyers, battleships, carriers);
	Game g(b, p1, p2);
	g.play();
}