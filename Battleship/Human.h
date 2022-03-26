#pragma once
#include "Player.h"

class Human : public Player {
	int hits;
	void setShips(char board[10][10], int howBig, int counter);
public:
	Human();
	int getHits();

	void setBoard(char board[10][10]);
	bool shoot(char hidden[10][10], char visible[10][10]);
};