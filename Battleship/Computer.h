#pragma once
#include "Player.h"

class Computer : public Player {
	int hits;
	void setShips(int whichPlayer, int howBig, int counter, Board& b);
public:
	Computer();
	int getHits();

	void setBoard(int whichPlayer, Board& b);
	bool hitOrMiss(int whichPlayer, Board& b, int x, int y);
	bool shoot(int whichPlayer, Board& b);
};