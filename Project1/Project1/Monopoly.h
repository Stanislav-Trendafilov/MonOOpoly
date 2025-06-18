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
	int thrownTupples;
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
	void printBuildMenu() const;
	void startGame();	
	int rollDice();
	void printDice(int num) const;
	void stepOnField(size_t moveWithSteps);
	
	void setCurrentTurnPlayerIndex(int index);
	void setThrownTupples(int tupples);

	const Player& getPlayerOnTurn() const;
	Player& getPlayerOnTurn();
	void getInfoAboutPlayerOnTurn() const;
	int getRollTupplesCount() const;

	void printBoard() const;
	void printBoardWithPlayers() const;

	const Player& getPlayer(int index) const;
	Player& getPlayer(int index);
	const MyVector<Player>& getPlayers() const;
	MyVector<Player>& getPlayers();

	void PlayTurn();

};

