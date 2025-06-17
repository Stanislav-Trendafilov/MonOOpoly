#include "Engine.h"

Engine::Engine()
{
	monopolyGame = Monopoly::getInstance();
}

void Engine::run()
{
	monopolyGame->startGame();

	int moveWith=monopolyGame->rollDice();

	monopolyGame->stepOnField(moveWith);
	
	monopolyGame->getInfoAboutPlayerOnTurn();
	monopolyGame->printBoardWithPlayers();
	
	moveWith = monopolyGame->rollDice();
	monopolyGame->stepOnField(moveWith);
	
	monopolyGame->getInfoAboutPlayerOnTurn();
	
	moveWith = monopolyGame->rollDice();
	monopolyGame->stepOnField(moveWith);
	
	monopolyGame->getInfoAboutPlayerOnTurn();

	
}
