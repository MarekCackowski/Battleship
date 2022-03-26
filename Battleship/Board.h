#pragma once

class Board {
private:
	int patrolBoats, destroyers, battleships, carriers;
public:
	char visible1[10][10], visible2[10][10], hidden1[10][10], hidden2[10][10];

	Board() = default;
	Board(int patrolBoats, int destroyers, int battleships, int carriers);
	~Board() = default;
	int getPatrolBoats();
	int getDestroyers();
	int getBattleships();
	int getCarriers();

	void showBoard(char board[10][10]);
	void placeShip(int howBig, char board[10][10], int choice, int x, int y);
	bool checkShipPlacement(int howBig, char board[10][10], int choice, int x, int y);
};