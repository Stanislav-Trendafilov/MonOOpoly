#pragma once
#include "Field.h"
#include "Player.h"
#include "MyVector.hpp"
#include "HeterogeneousContainer.hpp"
#include "CardDeck.h"

class Board
{
	Board();
	static Board* instance;
	HeterogeneousContainer<Field> fields;
	CardDeck* deck;
	MyVector<Player> players;
public:
	void InitializeBoard();
	static Board* getInstance();
	static void destroyInstance();
};

