#pragma once
#include "Player.h"
#include "Board.h"
#include "Bank.h"
#include "CardDeck.h"
#include "Constants.h"
#include "MyVector.hpp"

class Monopoly
{
	Monopoly();
	int currentTurnPlayerIndex;
	static Monopoly* instance;

	MyVector<Player> players;
	Board* board;
	CardDeck* cardDeck;
	Bank* bank;

	void addPlayers();
	void addPlayer(const Player& player);
	void removePlayer(int playerIndex);
public:
	static Monopoly* getInstance();
	static void destroyInstance();

	void printInstructions() const;
	void startGame();	
	int rollDice() const;
	void printDice(int num) const;
	void stepOnCard();

	const Player& getPlayerOnTurn() const;
	Player& getPlayerOnTurn();
	const Player& getPlayer(int index) const;
	Player& getPlayer(int index);
	const MyVector<Player>& getPlayers() const;
	MyVector<Player>& getPlayers();

	void PlayTurn();

};

