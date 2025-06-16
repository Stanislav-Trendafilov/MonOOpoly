#include "Monopoly.h"
#include <random>


Monopoly::Monopoly()
{
	currentTurnPlayerIndex = 1;
	board = Board::getInstance();
	cardDeck = CardDeck::getInstance();
}

Monopoly* Monopoly::instance = nullptr;

Monopoly* Monopoly::getInstance()
{
	if (!instance)
	{
		instance = new Monopoly();
	}
	return instance;
}

void Monopoly::destroyInstance()
{
	delete instance;
	instance = nullptr;
}

void Monopoly::startGame()
{
	std::cout << "Welcome to my final project of the course OOP_Practicum :)" << std::endl;
	std::cout << "Starting Monopoly game..." << std::endl;
	std::cout << "!Press any key to start the game!" << std::endl;
	std::cin.get();

	addPlayers();
}

void Monopoly::addPlayers()
{
	int playersCount;

	std::cout << "Enter number of players, who will play the current game (2-6): ";
	std::cin >> playersCount;
	while (playersCount < 2 || playersCount > 6)
	{
		std::cout << "Invalid number of players. Please enter a number between 2 and 6: ";
		std::cin >> playersCount;
	}
	for (int i = 0; i < playersCount; i++)
	{
		std::cout << "Enter username for player No " << i + 1 << ": ";
		MyString username;
		std::cin >> username;
		Player player(username);
		addPlayer(player);
		std::cout << "Player " << username << " added successfully!" << std::endl;
		std::cout << "Now you are able to enjoy the game." << std::endl;
	}
	std::cout << "All players added successfully!" << std::endl;

	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "Here you can see the Monopoly board" << std::endl;
	std::cout << "As you can see, most of the locations are well known for most of the Bulgarians " << std::endl;
	board->PrintBoard();
	
}

void Monopoly::addPlayer(const Player& player)
{
	players.push_back(player);
}

void Monopoly::removePlayer(int playerIndex)
{
	players.remove(playerIndex);
}

int Monopoly::rollDice() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(GlobalConstants::DICE_VALUE1, GlobalConstants::DICE_VALUE6);

	int firstDie = dis(gen);
	int secondDie = dis(gen);
	
	std::cout << "You have rolled: "<<std::endl;

	printDice(firstDie);
	printDice(secondDie);

	std::cout << "   Total: " << firstDie + secondDie << std::endl;
	return firstDie + secondDie;
}

void Monopoly::printDice(int num) const
{
	if (num == GlobalConstants::DICE_VALUE1)
	{
		std::cout << "   +-------+" << std::endl;
		std::cout << "   |       |" << std::endl;
		std::cout << "   |   *   |" << std::endl;
		std::cout << "   |       |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}
	else if (num == GlobalConstants::DICE_VALUE2)
	{
		std::cout << "   +-------+" << std::endl;
		std::cout << "   |   *   |" << std::endl;
		std::cout << "   |       |" << std::endl;
		std::cout << "   |   *   |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}				     
	else if (num == GlobalConstants::DICE_VALUE3)   
	{				     
		std::cout << "   +-------+" << std::endl;
		std::cout << "   |     * |" << std::endl;
		std::cout << "   |   *   |" << std::endl;
		std::cout << "   | *     |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}				     
	else if (num == GlobalConstants::DICE_VALUE4)   
	{				     
		std::cout << "   +-------+" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   |       |" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}				     
	else if (num == GlobalConstants::DICE_VALUE5)   
	{				     
		std::cout << "   +-------+" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   |   *   |" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}				     
	else if (num == GlobalConstants::DICE_VALUE6)   
	{				     
		std::cout << "   +-------+" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   | *   * |" << std::endl;
		std::cout << "   +-------+" << std::endl;
	}				     
}

void Monopoly::stepOnCard()
{
}

const Player& Monopoly::getPlayerOnTurn() const
{
	return players[currentTurnPlayerIndex]; 
}

Player& Monopoly::getPlayerOnTurn()
{
	return players[currentTurnPlayerIndex]; 
}

const Player& Monopoly::getPlayer(int playerIndex) const
{ 

	if (playerIndex <=0 || playerIndex > players.size()) 
	{
		throw std::out_of_range("Player not found");
	}
	return players[playerIndex - 1];
}

Player& Monopoly::getPlayer(int index)
{
	if (index <= 0 || index > players.size())
	{
		throw std::out_of_range("Player not found");
	}
	return players[index - 1];
}

const MyVector<Player>& Monopoly::getPlayers() const
{
	return players;
}

MyVector<Player>& Monopoly::getPlayers()
{
	return players;
}

void Monopoly::PlayTurn()
{

}

