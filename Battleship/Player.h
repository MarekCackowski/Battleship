#pragma once

#include "Board.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player {
	virtual void setShips(int whichPlayer, int howBig, int counter, Board& b) = 0;
public:
	virtual int getHits() = 0;
	virtual void setBoard(int whichPlayer, Board& b) = 0;
	virtual bool shoot(int whichPlayer, Board& b) = 0;
};
#endif