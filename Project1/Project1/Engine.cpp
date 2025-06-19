#include "Engine.h"
#include "Trade.h"

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
		std::cout << "7. End Turn" << std::endl;

		monopolyGame->setThrownTupples(0);

		while (!turnEnded)
		{
			std::cout << "\nEnter your action: ";

			int turnAction;
			std::cin >> turnAction;

			int newPlayerTurnIndex, moveWith, number, priceForBuilding, targetPlayerId, offerType, requestType, offerMoney, offerPropIndex, requestMoney, requestPropIndex;

			int countValidTradeProperties;

			bool canBuild = true;

			Player* targetPlayer = nullptr;
			MyVector<Property* >validForBuildProps;
			Trade trade;

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
					if (monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getrentLevel() > 0)
					{
						std::cout << i << ". " << monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getName() << std::endl;
						validForBuildProps.push_back(monopolyGame->getPlayerOnTurn().getMyProperties()[i]);
					}

				}

				if (validForBuildProps.size() == 0)
				{
					std::cout << "You have no properties to build on." << std::endl;
					break;
				}

				std::cout << "Enter the property number you want to build on:" << std::endl;

				std::cin >> number;

				while (number < 0)
				{
					std::cout << "Invalid property number. Try again." << std::endl;
					std::cin >> number;
				}

				for (size_t i = 0; i < validForBuildProps.size(); i++)
				{
					GlobalConstants::PropertyColors color = validForBuildProps[i]->getColor();

					if (monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getColor() == color
						&& validForBuildProps[i]->getrentLevel() < monopolyGame->getPlayerOnTurn().getMyProperties()[number]->getrentLevel())
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
				std::cout << "Do you really want to buy a house on property (" << number << ")  (y/n)" << std::endl;

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

				std::cout << "Available players to trade with:" << std::endl;
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

				if (targetPlayerId < 0 || targetPlayerId > monopolyGame->getPlayers().size() - 1)
				{
					std::cout << "Invalid player ID." << std::endl;
					break;
				}

				//////logic///////

				targetPlayer = &monopolyGame->getPlayer(targetPlayerId);

				trade = Trade(&monopolyGame->getPlayerOnTurn(), targetPlayer);

				std::cout << "\nWhat do you want to offer?" << std::endl;
				std::cout << "1. Money" << std::endl;
				std::cout << "2. Property" << std::endl;
				std::cout << "3. Train Station" << std::endl;
				std::cout << "4. Utility" << std::endl;

				offerType;
				std::cin >> offerType;

				while (offerType < 1 || offerType > 4)
				{
					std::cout << "Invalid option. Please choose 1, 2, 3 or 4: " << std::endl;
					std::cin >> offerType;
				}

				std::cout << "You have successfully chosen option: " << offerType << std::endl;

				if (offerType == 1)
				{
					std::cout << "\nEnter amount of money to OFFER: ";
					std::cin >> offerMoney;

					while (offerMoney > monopolyGame->getPlayerOnTurn().getMoney())
					{
						std::cout << "You don't have enough money." << std::endl;
						std::cin >> offerMoney;
					}
					trade.setOfferedMoney(offerMoney);

				}
				else if (offerType == 2)
				{
					countValidTradeProperties = 0;
					std::cout << "You can trade only properties without houses on them" << std::endl;
					std::cout << "Your properties:" << std::endl;
					for (size_t i = 0; i < monopolyGame->getPlayerOnTurn().getMyProperties().size(); i++)
					{
						if (monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getrentLevel() <= 1)
						{
							std::cout << "  [" << i << "] " << monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getName() << std::endl;
							countValidTradeProperties++;
						}
					}
					if (countValidTradeProperties > 0)
					{
						std::cout << "Enter index of PROPERTY to OFFER: ";
						std::cin >> offerPropIndex;

						Property* offerProperty = nullptr;


						if (offerPropIndex >= 0 && offerPropIndex < monopolyGame->getPlayerOnTurn().getMyProperties().size())
						{
							offerProperty = monopolyGame->getPlayerOnTurn().getMyProperties()[offerPropIndex];
						}

						trade.setOfferedProperty(offerProperty);
					}
					else
					{
						std::cout << "You have no properties to trade." << std::endl;
					}
				}
				else if (offerType == 3)
				{
					std::cout << "Your train stations:" << std::endl;
					if(monopolyGame->getPlayerOnTurn().getMyStations().size() == 0)
					{
						std::cout << "You have no train stations to trade." << std::endl;
						break;
					}
					for (size_t i = 0; i < monopolyGame->getPlayerOnTurn().getMyStations().size(); i++)
					{
						std::cout << "  [" << i << "] " << monopolyGame->getPlayerOnTurn().getMyStations()[i]->getName() << std::endl;
					}
					std::cout << "Enter index of TRAIN STATION to OFFER: ";
					std::cin >> offerPropIndex;

					TrainStation* offerTrainStation = nullptr;

					if (offerPropIndex >= 0 && offerPropIndex < monopolyGame->getPlayerOnTurn().getMyStations().size())
					{
						offerTrainStation = monopolyGame->getPlayerOnTurn().getMyStations()[offerPropIndex];
					}
					trade.setOfferedTrainStation(offerTrainStation);
				}
				else if (offerType == 4)
				{
					std::cout << "Your utilities:" << std::endl;
					if(monopolyGame->getPlayerOnTurn().getMyUtilities().size() == 0)
					{
						std::cout << "You have no utilities to trade." << std::endl;
						break;
					}
					for (size_t i = 0; i < monopolyGame->getPlayerOnTurn().getMyUtilities().size(); i++)
					{
						std::cout << "  [" << i << "] " << monopolyGame->getPlayerOnTurn().getMyUtilities()[i]->getName() << std::endl;
					}

					std::cout << "Enter index of UTILITY to OFFER: ";
					std::cin >> offerPropIndex;

					CompanyField* offerUtility = nullptr;

					if (offerPropIndex >= 0 && offerPropIndex < monopolyGame->getPlayerOnTurn().getMyUtilities().size())
					{
						offerUtility = monopolyGame->getPlayerOnTurn().getMyUtilities()[offerPropIndex];
					}
					trade.setOfferedCompanyField(offerUtility);
				}

				std::cout << "\nWhat do you want in return?" << std::endl;
				std::cout << "1. Money" << std::endl;
				std::cout << "2. Property" << std::endl;
				std::cout << "3. Train Station" << std::endl;
				std::cout << "4. Utility" << std::endl;

				requestType;
				std::cin >> requestType;

				while (requestType < 1 || requestType > 4)
				{
					std::cout << "Invalid option. Please choose 1, 2, 3 or 4: " << std::endl;
					std::cin >> requestType;
				}

				std::cout << "You have successfully chosen option: " << requestType << std::endl;

				if (requestType == 1)
				{
					std::cout << "\nEnter amount of money to REQUEST: ";
					std::cin >> requestMoney;

					while (requestMoney > targetPlayer->getMoney())
					{
						std::cout << targetPlayer->getPlayerName() << " doesn't have that much money." << std::endl;
						std::cin >> requestMoney;
					}
					trade.setRequestedMoney(requestMoney);
				}
				else if (requestType == 2)
				{
					std::cout << "You can ask only for properties without houses on them" << std::endl;
					std::cout << targetPlayer->getPlayerName() << "'s properties:" << std::endl;

					countValidTradeProperties = 0;
					for (size_t i = 0; i < targetPlayer->getMyProperties().size(); i++)
					{
						if (targetPlayer->getMyProperties()[i]->getrentLevel() <= 1)
						{
							std::cout << "  [" << i << "] " << targetPlayer->getMyProperties()[i]->getName() << std::endl;
							countValidTradeProperties++;
						}
					}
					if(countValidTradeProperties == 0)
					{
						std::cout << targetPlayer->getPlayerName() << " has no properties to trade." << std::endl;
						break;
					}
					std::cout << "Enter index of PROPERTY to REQUEST: ";
					std::cin >> requestPropIndex;

					Property* requestProp = nullptr;

					if (requestPropIndex >= 0 && requestPropIndex < targetPlayer->getMyProperties().size())
					{
						requestProp = targetPlayer->getMyProperties()[requestPropIndex];
					}

					trade.setRequestedProperty(requestProp);
				}
				else if (requestType == 3)
				{
					std::cout << targetPlayer->getPlayerName() << "'s train stations:" << std::endl;
					if(targetPlayer->getMyStations().size() == 0)
					{
						std::cout << targetPlayer->getPlayerName() << " has no train stations to trade." << std::endl;
						break;
					}
					for (size_t i = 0; i < targetPlayer->getMyStations().size(); i++)
					{
						std::cout << "  [" << i << "] " << targetPlayer->getMyStations()[i]->getName() << std::endl;
					}
					std::cout << "Enter index of TRAIN STATION to REQUEST: ";
					std::cin >> requestPropIndex;
					TrainStation* requestTrainStation = nullptr;
					if (requestPropIndex >= 0 && requestPropIndex < targetPlayer->getMyStations().size())
					{
						requestTrainStation = targetPlayer->getMyStations()[requestPropIndex];
					}
					trade.setRequestedTrainStation(requestTrainStation);
				}
				else if (requestType == 4)
				{
					std::cout << targetPlayer->getPlayerName() << "'s utilities:" << std::endl;
					if(targetPlayer->getMyUtilities().size() == 0)
					{
						std::cout << targetPlayer->getPlayerName() << " has no utilities to trade." << std::endl;
						break;
					}
					for (size_t i = 0; i < targetPlayer->getMyUtilities().size(); i++)
					{
						std::cout << "  [" << i << "] " << targetPlayer->getMyUtilities()[i]->getName() << std::endl;
					}

					std::cout << "Enter index of UTILITY to REQUEST: ";
					std::cin >> requestPropIndex;

					CompanyField* requestUtility = nullptr;
					if (requestPropIndex >= 0 && requestPropIndex < targetPlayer->getMyUtilities().size())
					{
						requestUtility = targetPlayer->getMyUtilities()[requestPropIndex];
					}
					trade.setRequestedCompanyField(requestUtility);
				}

				std::cout << "\nTrade offer has been sent to " << targetPlayer->getPlayerName() << "." << std::endl;

				trade.showTradeOffer();

				std::cout << targetPlayer->getPlayerName() << ", do you accept the trade? (y/n): ";

				char answer;
				std::cin >> answer;

				if (answer == 'y' || answer == 'Y')
				{
					trade.applyTrade();
					std::cout << "Trade accepted! Assets are exchanged." << std::endl;

				}
				else
				{
					std::cout << "Trade declined." << std::endl;
				}
				break;

			case 6:
				std::cout << "[Mortgage a property]" << std::endl;
				break;

			case 7:
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
