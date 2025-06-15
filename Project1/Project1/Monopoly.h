#pragma once
#include "Player.h"
#include "Board.h"
#include "Bank.h"
#include "CardDeck.h"
#include "MyVector.hpp"

class Monopoly
{
	Monopoly();
	static Monopoly* instance;

	MyVector<Player> players;
	Board* board;
	CardDeck* cardDeck;
	Bank* bank;
public:



	static Monopoly* getInstance();
	static void destroyInstance();
	

};

