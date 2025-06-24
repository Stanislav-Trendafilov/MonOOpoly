#pragma once
#include "Monopoly.h"

class Engine
{
	Monopoly* monopolyGame;
	bool turnEnded = false;
	bool rollDice = false;
public:
	Engine();
	void run();

	void saveToBinaryFile();
	void loadFromBinaryFile();
};

