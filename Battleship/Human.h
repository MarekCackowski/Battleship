#pragma once
#include "Player.h"

class Human : public Player {
	int hits;
	void setShips(int whichPlayer, int howBig, int counter, Board& b);
public:
	Human();
	int getHits();

	void setBoard(int whichPlayer, Board& b);
	bool shoot(int whichPlayer, Board& b);
};