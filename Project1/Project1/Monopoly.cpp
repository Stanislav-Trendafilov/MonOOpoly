#include "Monopoly.h"
#include <random>


Monopoly::Monopoly()
{
	currentTurnPlayerIndex = 0;
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

	printInstructions();

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
		Player player(i,username);
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

void Monopoly::printInstructions() const {
	std::cout << "\n========== MONOPOLY GAME INSTRUCTIONS =========="<<std::endl;
	std::cout << "Welcome to the OOP_Practicum Monopoly Game" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "--> Objective <--" << std::endl;
	std::cout << "  Become the richest player by buying properties, collecting rent, and avoiding bankruptcy." << std::endl;
	std::cout << "" << std::endl;

	std::cout << "--> Game Flow:" << std::endl;
	std::cout << "  1. Each player takes turns in clockwise order." << std::endl;
	std::cout << "  2. On your turn, press a key to roll the dices." << std::endl;
	std::cout << "  3. Move forward the number of steps equal to the sum of the dices." << std::endl;
	std::cout << "  4. The field you land on may allow you to:" << std::endl;
	std::cout << "     - Buy a property" << std::endl;
	std::cout << "     - Pay rent to another player" << std::endl;
	std::cout << "     - Draw a card with special effects" << std::endl;
	std::cout << "     - Go to jail or pass 'Start'" << std::endl;
	std::cout << "  5. After finishing your turn, the next player proceeds." << std::endl;
	std::cout << "" << std::endl;

	std::cout << "--> Money and Bank:" << std::endl;
	std::cout << "  - All players start with a fixed amount of money (1500$)." << std::endl;
	std::cout << "  - If you land on someone else's property, you must pay rent." << std::endl;
	std::cout << "  - If you run out of money, you're bancrupted and then eliminated." << std::endl;
	std::cout << "" << std::endl;

	std::cout << "--> Properties:" << std::endl;
	std::cout << "  - You can buy unowned properties." << std::endl;
	std::cout << "  - You earn rent whenever others land on your properties." << std::endl;
	std::cout << "  - Some cards or actions may upgrade/downgrade properties." << std::endl;
	std::cout << "" << std::endl;

	std::cout << "--> Special Spaces:" << std::endl;
	std::cout << "  - 'Go to Jail' sends you to jail." << std::endl;
	std::cout << "  - 'Chance' or 'Community Chest' triggers a card." << std::endl;
	std::cout << "  - 'Free Parking' is just a rest spot." << std::endl;
	std::cout << "" << std::endl;

	std::cout << "--> Victory:" << std::endl;
	std::cout << "  - The last player remaining (all others bankrupt) is the winner!" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "-- > Tips:" << std::endl;
	std::cout << "  - Buy strategically. Save money for rent and fees." << std::endl;
	std::cout << "  - Be careful not to go bankrupt." << std::endl;
	std::cout << "  - Most importantly, have fun!" << std::endl;

	std::cout << "===============================================" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "!Press any key to start the game!" << std::endl;
	std::cin.get();

};

int Monopoly::rollDice() const
{
	std::cout << "Press enter to roll the dices...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//use in order to ignore any previous input
	std::cin.get();				  

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

void Monopoly::stepOnField(size_t moveWithSteps)
{
	getPlayerOnTurn().moveToLocation(getPlayerOnTurn().getCurrentPosition() + moveWithSteps);
	board->activateFieldEffect(getPlayerOnTurn());
}

const Player& Monopoly::getPlayerOnTurn() const
{
	return players[currentTurnPlayerIndex]; 
}

Player& Monopoly::getPlayerOnTurn()
{
	return players[currentTurnPlayerIndex]; 
}

void Monopoly::getInfoAboutPlayerOnTurn() const
{
	Player player = getPlayerOnTurn();
	std::cout << "Player "<<player.getPlayerId() <<" on turn: " << player.getPlayerName() << std::endl;
	std::cout << "Current position: " << player.getCurrentPosition() << std::endl;
	std::cout << "Money: " << player.getMoney() << std::endl;
}

void Monopoly::printBoardWithPlayers() const
{
	board->PrintBoard(getPlayers());
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

