#pragma once

class Board {
private:
	int patrolBoats, destroyers, battleships, carriers;
public:
	char visible[2][10][10], hidden[2][10][10];
	Board() = default;
	Board(int patrolBoats, int destroyers, int battleships, int carriers);
	~Board() = default;
	int getPatrolBoats();
	int getDestroyers();
	int getBattleships();
	int getCarriers();

	void showVisibleBoard(int whichPlayer);
	void showHiddenBoard(int whichPlayer);
	void placeShip(int howBig, int whichPlayer, int choice, int& x, int& y);
	bool checkShipPlacement(int howBig, int whichPlayer, int choice, int x, int y);
};