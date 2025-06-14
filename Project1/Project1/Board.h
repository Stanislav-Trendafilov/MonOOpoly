#pragma once
#include "Field.h"
#include "Player.h"
#include "MyVector.hpp"
#include "HeterogeneousContainer.hpp"
#include "CardDeck.h"
#include "CardField.h"

class Board
{
	Board();
	static Board* instance;
	HeterogeneousContainer<Field> fields;
	CardDeck* deck;

public:
	void InitializeBoard();
	void PrintBoard() const;
	static Board* getInstance();
	static void destroyInstance();
};

