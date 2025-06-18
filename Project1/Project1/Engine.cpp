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

		monopolyGame->setThrownTupples(0);

		while (!turnEnded)
		{
			std::cout << "\nEnter your action: ";

			int turnAction;
			std::cin >> turnAction;

			int newPlayerTurnIndex, moveWith,number, priceForBuilding;

			MyVector<int>validForBuildIndexes;

			switch (turnAction)
			{
				case 1:
					if (rollDice)
					{
						std::cout << "You have already rolled the dice this turn." << std::endl;
						continue;
					}

					std::cout << "[You chose to roll the dice]" << std::endl;		

					if (monopolyGame->getPlayerOnTurn().isJailed())
					{
						std::cout << "Do you want to exit jail for 100$ (y/n)";
						char choice;
						std::cin >> choice;

						if (choice == 'y' || choice == 'Y')
						{
							monopolyGame->getPlayerOnTurn().goOutOfPrison();
							std::cout << "You left prison successfully!" << std::endl;
						}
						else {
							std::cout << "You chose not to exit prison and try your luck." << std::endl;
						}

					}

					moveWith = monopolyGame->rollDice();

					if (monopolyGame->getPlayerOnTurn().isJailed())
					{
						if (monopolyGame->getRollTupplesCount() == 1)
						{
							std::cout << "You rolled a double! You can leave jail." << std::endl;
							monopolyGame->getPlayerOnTurn().goOutOfPrison();
							rollDice = true;
							monopolyGame->getPlayerOnTurn().setRoll(moveWith);//in order to use it in utility functions
							monopolyGame->stepOnField(moveWith);
						}
						else
						{
							std::cout << "You rolled a non-double. You must stay in jail." << std::endl;
						}
					}
					else
					{
						if (monopolyGame->getRollTupplesCount() == 0)
						{
							rollDice = true;
						}
						else if (monopolyGame->getRollTupplesCount() == 3)
						{
							std::cout << "You rolled a double three times in a row! You must go to jail." << std::endl;
							monopolyGame->getPlayerOnTurn().goInPrison();
							rollDice = true;
							continue;
						}
						monopolyGame->getPlayerOnTurn().setRoll(moveWith);//in order to use it in utility functions
						monopolyGame->stepOnField(moveWith);
					}

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
					monopolyGame->printBuildMenu();

								
					for (size_t i = 0; i < monopolyGame->getPlayerOnTurn().getMyProperties().size(); i++)
					{			 
						if(monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getrentLevel()>0)
						{
							std::cout << i << ". " << monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getName() << std::endl;
							validForBuildIndexes.push_back(i);
						}

					}
					std::cout << "Enter the property number you want to build on:" << std::endl;
					
					std::cin >> number;
					while (number <0)
					{
						std::cout << "Invalid property number. Try again." << std::endl;
						std::cin >> number;
					}


					priceForBuilding = monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getPriceForBuilding();
					std::cout << "Building price for property is " << priceForBuilding << "$" << std::endl;
					std::cout << "Do you really want to buy a house on property ("<<number <<")  (y/n)" << std::endl;

					char choice;
					std::cin >> choice;

					if (choice == 'y' || choice == 'Y')
					{
						monopolyGame->getPlayerOnTurn().getMyProperties()[number]->buildHouse();
						monopolyGame->getPlayerOnTurn().subtractMoney(priceForBuilding);
					}
					else 
					{
						std::cout << "You chose not to build houses." << std::endl;
					}

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
