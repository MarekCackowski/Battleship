#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
	virtual void setShips(char board[10][10], int howBig, int counter) = 0;
public:
	virtual int getHits() = 0;
	virtual void setBoard(char board[10][10]) = 0;
	virtual bool shoot(char hidden[10][10], char visible[10][10]) = 0;
};
#endif