#pragma once
#include "Board.h"
#include "Computer.h"
#include "Human.h"

#ifndef BOARD_H
#define BOARD_H

class Game {
	bool isEnded;
	Board b;
	Player *p1, *p2;
public:
	Game(Board& b, Player*& p1, Player*& p2);
	~Game() = default;
	void play();
};

#endif