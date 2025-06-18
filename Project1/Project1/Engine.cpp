#include "Engine.h"

Engine::Engine()
{
	monopolyGame = Monopoly::getInstance();
}

void Engine::run()
{
	monopolyGame->startGame();

	while (true)
	{
		bool turnEnded = false;
		bool rollDice = false;
		std::cout << "====>  Player " << monopolyGame->getPlayerOnTurn().getPlayerName() << " Turn Menu  <====" << std::endl;
		std::cout << "(Here are all types of action)" << std::endl;
		std::cout << "1. Roll Dice" << std::endl;
		std::cout << "2. View Player Info" << std::endl;
		std::cout << "3. View Board" << std::endl;
		std::cout << "4. Build House/Hotel" << std::endl;
		std::cout << "5. Trade with Player" << std::endl;
		std::cout << "6. Mortgage Property" << std::endl;
		std::cout << "7. Unmortgage Property" << std::endl;
		std::cout << "8. End Turn" << std::endl;

		while (!turnEnded)
		{
			std::cout << "\nEnter your action: ";

			int turnAction;
			std::cin >> turnAction;

			int newPlayerTurnIndex, moveWith;

			switch (turnAction)
			{
				case 1:
					if (rollDice)
					{
						std::cout << "You have already rolled the dice this turn." << std::endl;
						continue;
					}												   
					std::cout << "[You chose to roll the dice]" << std::endl;
					moveWith = monopolyGame->rollDice();
					monopolyGame->stepOnField(12);
					monopolyGame->stepOnField(16);
					rollDice = true;
					break;

				case 2:
					std::cout << "[Displaying player info]" << std::endl;
					monopolyGame->getInfoAboutPlayerOnTurn();
					break;

				case 3:
					std::cout << "[Displaying board]" << std::endl;
					monopolyGame->printBoard();
					break;

				case 4:
					std::cout << "[Build menu]" << std::endl;

					break;

				case 5:
					std::cout << "[Initiating trade]" << std::endl;

					break;

				case 6:
					std::cout << "[Mortgage a property]" << std::endl;

					break;

				case 7:
					std::cout << "[Unmortgage a property]" << std::endl;

					break;

				case 8:
					std::cout << "[Turn ended]" << std::endl;
					if (rollDice)
					{
						turnEnded = true;

						newPlayerTurnIndex = monopolyGame->getPlayerOnTurn().getPlayerId() + 1;

						if (newPlayerTurnIndex >= monopolyGame->getPlayers().size())
						{
							newPlayerTurnIndex = 0;
						}

						monopolyGame->setCurrentTurnPlayerIndex(newPlayerTurnIndex);
					}
					else
					{
						std::cout << "You must roll the dice before ending your turn." << std::endl;
					}

					break;

				default:
					std::cout << "Invalid option. Try again." << std::endl;
					break;
			}
		}
	}

	monopolyGame->destroyInstance();
}
