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

			int newPlayerTurnIndex, moveWith,number, priceForBuilding, targetPlayerId,offerType, requestType,offerMoney;

			bool canBuild = true;

			Player targetPlayer;
			MyVector<Property* >validForBuildProps;

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
							validForBuildProps.push_back(monopolyGame->getPlayerOnTurn().getMyProperties()[i]);
						}

					}

					if(validForBuildProps.size() == 0)
					{
						std::cout << "You have no properties to build on." << std::endl;
						break;
					}
															    
					std::cout << "Enter the property number you want to build on:" << std::endl;
					
					std::cin >> number;

					while (number <0)
					{
						std::cout << "Invalid property number. Try again." << std::endl;
						std::cin >> number;
					}

					for (size_t i = 0; i < validForBuildProps.size(); i++)
					{
						GlobalConstants::PropertyColors color = validForBuildProps[i]->getColor();

						if (monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getColor() == color
							&& validForBuildProps[i]->getrentLevel()< monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getrentLevel())
						{
							std::cout << "Firstly, you will have to build on other properties with this color." << std::endl;
							canBuild = false;
							break;
							 
						}

					}

					if (!canBuild)
					{
						break;
					}

					priceForBuilding = monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getPriceForBuilding();
					std::cout << "Building price for property is " << priceForBuilding << "$" << std::endl;
					std::cout << "Do you really want to buy a house on property ("<<number <<")  (y/n)" << std::endl;

					char choice;
					std::cin >> choice;

					if (choice == 'y' || choice == 'Y')
					{
						if (monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getrentLevel() == GlobalConstants::MAX_BUILDINGS_PROPERTY - 1)
						{
							std::cout << "You cannot build more houses on this property." << std::endl;
							break;
						}
						else
						{
							monopolyGame->getPlayerOnTurn().getMyProperties()[number]->buildHouse();
							monopolyGame->getPlayerOnTurn().subtractMoney(priceForBuilding);
						}
					}
					else 
					{
						std::cout << "You chose not to build houses." << std::endl;
					}

					break;

				case 5:

					monopolyGame->printTradeMenu();

					std::cout << "Available players to trade with:"<< std::endl;
					for (size_t i = 0; i < monopolyGame->getPlayers().size(); i++) 
					{
						if (monopolyGame->getPlayers()[i].getPlayerId() != monopolyGame->getPlayerOnTurn().getPlayerId())
						{
							std::cout << " - [" << monopolyGame->getPlayers()[i].getPlayerId() << "] " << monopolyGame->getPlayers()[i].getPlayerName() << std::endl;
						}
					}

					std::cout << "Enter the ID of the player you want to trade with: ";

					std::cin >> targetPlayerId;

					if (targetPlayerId == monopolyGame->getPlayerOnTurn().getPlayerId()) 
					{
						std::cout << "You cannot trade with yourself." << std::endl;
						break;
					}

					if (targetPlayerId < 0 || targetPlayerId > monopolyGame->getPlayers().size()-1) 
					{
						std::cout << "Invalid player ID." << std::endl;
						break;
					}

					targetPlayer = monopolyGame->getPlayer(targetPlayerId);

					std::cout << "\nWhat do you want to offer?" << std::endl;
					std::cout << "1. Money" << std::endl;
					std::cout << "2. Property" << std::endl;
					std::cout << "3. Both" << std::endl;


					offerType;
					std::cin >> offerType;



					while (offerType < 1 || offerType > 3)
					{
						std::cout << "Invalid option. Please choose 1, 2, or 3: " << std::endl;
						std::cin >> offerType;
					}

					std::cout << "You have successfully chosen option: " << offerType << std::endl;

					std::cout << "\nWhat do you want in return?" << std::endl;
					std::cout << "1. Money" << std::endl;
					std::cout << "2. Property" << std::endl;
					std::cout << "3. Both" << std::endl;

					requestType;
					std::cin >> requestType;

					while (requestType < 1 || requestType > 3)
					{
						std::cout << "Invalid option. Please choose 1, 2, or 3: " << std::endl;
						std::cin >> requestType;
					}

					std::cout << "You have successfully chosen option: " << requestType << std::endl;

					std::cout << "\nTrade offer has been sent to " << targetPlayer.getPlayerName() << "."<<std::endl;
					std::cout << targetPlayer.getPlayerName() << ", do you accept the trade? (y/n): ";

					char answer;
					std::cin >> answer;

					if (answer == 'y' || answer == 'Y')
					{
						std::cout << "Trade accepted! Assets are exchanged." << std::endl;

					}
					else
					{
						std::cout << "Trade declined."<<std::endl;
					}
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
