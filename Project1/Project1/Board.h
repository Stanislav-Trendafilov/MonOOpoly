#pragma once
#include "Field.h"
#include "Player.h"
#include "MyVector.hpp"
#include "CardDeck.h"

class Board
{
	Board();
	static Board* instance;
	CardDeck* deck;
	MyVector<Player> players;
public:
	static Board* getInstance();
	static void destroyInstance();
};

