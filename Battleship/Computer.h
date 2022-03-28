#pragma once
#include "Player.h"

class Computer : public Player {
	int hits;
	void setShips(int whichPlayer, int howBig, int counter, Board& b);
public:
	Computer();
	int getHits();

	void setBoard(int whichPlayer, Board& b);
	bool shoot(int whichPlayer, Board& b);
};