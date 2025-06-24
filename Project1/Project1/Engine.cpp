#include "Engine.h"
#include "Trade.h"
#include "windows.h"

Engine::Engine()
{
	monopolyGame = Monopoly::getInstance();
}

void Engine::run()
{
	system("Color 0E");

	std::cout << "You can choose to load game(0) or start new one(1): ";
	int option;
	std::cin >> option;

	while (std::cin.fail() || option > 1 || option < 0)
	{
		std::cin.clear();
		std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
		std::cout << "Invalid option. Try again.";
		std::cin >> option;
	}

	if (option == 0)
	{
		monopolyGame->printInstructions();

		loadFromBinaryFile();
	}
	else
	{
		monopolyGame->startGame();;
	}

	while (monopolyGame->getValidPlayers()>1)
	{
		int newPlayerTurnIndex;

		if (!monopolyGame->getPlayerOnTurn().getIsInGame())
		{
			newPlayerTurnIndex = monopolyGame->getPlayerOnTurn().getPlayerId() + 1;

			if (newPlayerTurnIndex >= monopolyGame->getPlayers().size())
			{
				newPlayerTurnIndex = 0;
			}

			monopolyGame->setCurrentTurnPlayerIndex(newPlayerTurnIndex);
		}

		std::cout << "\n====>  Player " <<  monopolyGame->getPlayerOnTurn().getPlayerName() << " Turn Menu  <====" << std::endl;
		
		monopolyGame->printPlayerOptions();

		monopolyGame->setThrownTupples(0);

		turnEnded = false;
		rollDice = false;

		while (!turnEnded)
		{

			std::cout << "\nEnter your action: ";

			int turnAction;
			std::cin >> turnAction;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
				std::cout << "Invalid option. Try again." << std::endl;
				continue;
			}

			int countValidTradeProperties,mortgagedPropsCount, moveWith, number, priceForBuilding, targetPlayerId, offerType, requestType, offerMoney, offerPropIndex, requestMoney, requestPropIndex, mortgageValue;

			bool canBuild = true;

			Player* targetPlayer = nullptr;
			Property* mortgagedProps = nullptr;
			MyVector<Property* >validForBuildProps;
			MyVector<Property*> owned;
			Trade trade;

			switch (turnAction)
			{
			case 1:
			{
				if (rollDice)
				{
					std::cout << "You have already rolled the dice this turn." << std::endl;
					continue;
				}

				std::cout << "[You chose to roll the dice]" << std::endl;

				if (monopolyGame->getPlayerOnTurn().isJailed())
				{
					char choice;
					if (monopolyGame->getPlayerOnTurn().getRoundsInPrison() == 2)
					{
						std::cout << "You MIST leave jail and pay 100"<<std::endl;
						choice = 'y';
					}
					else
					{
						std::cout << "Do you want to exit jail for 100$ (y/n)";
						std::cin >> choice;

						if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						continue;
					}
					}


					if (choice == 'y' || choice == 'Y')
					{
						monopolyGame->getPlayerOnTurn().goOutOfPrison();
						monopolyGame->getPlayerOnTurn().subtractMoney(GlobalConstants::EXIT_JAIL_PRICE);
						std::cout << "You left prison successfully!" << std::endl;

						monopolyGame->getPlayerOnTurn().setRoundInPrison(0);
					}
					else
					{
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
						monopolyGame->getPlayerOnTurn().setRoundInPrison(0);

						rollDice = true;
						monopolyGame->getPlayerOnTurn().setRoll(moveWith);//in order to use it in utility functions
						monopolyGame->stepOnField(moveWith);
					}
					else
					{
						std::cout << "You rolled a non-double. You must stay in jail." << std::endl;
						monopolyGame->getPlayerOnTurn().setRoundInPrison(monopolyGame->getPlayerOnTurn().getRoundsInPrison()+1);
						rollDice = true;
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

				monopolyGame->printBoardWithPlayers();

				break;
			}
			case 2:
			{
				std::cout << "[Displaying player info]" << std::endl;
				monopolyGame->getInfoAboutPlayerOnTurn();
				break;
			}
			case 3:
			{
				std::cout << "[Displaying board]" << std::endl;
				monopolyGame->printBoardWithPlayers();
				break;
			}
			case 4:
			{	
				std::cout << "[Build menu]" << std::endl;
				monopolyGame->printBuildMenu();


				for (size_t i = 0; i < monopolyGame->getPlayerOnTurn().getMyProperties().size(); i++)
				{
					if (monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getrentLevel() > 0 && monopolyGame->checkStreetForMortgage(*monopolyGame->getPlayerOnTurn().getMyProperties()[i]))
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

				while (number < 0 || std::cin.fail()||number>validForBuildProps.size()-1)
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');

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
			}
			case 5:
			{
				monopolyGame->printTradeMenu();

				std::cout << "\nAvailable players to trade with:" << std::endl;
				for (size_t i = 0; i < monopolyGame->getPlayers().size(); i++)
				{
					if (monopolyGame->getPlayers()[i].getPlayerId() != monopolyGame->getPlayerOnTurn().getPlayerId())
					{
						std::cout << " - [" << monopolyGame->getPlayers()[i].getPlayerId() << "] " << monopolyGame->getPlayers()[i].getPlayerName() << std::endl;
					}
				}

				std::cout << "Enter the ID of the player you want to trade with: ";

				std::cin >> targetPlayerId;

				while (std::cin.fail() || targetPlayerId < GlobalConstants::MIN_PLAYER_INDEX
					|| targetPlayerId > monopolyGame->getPlayers().size() - 1
					|| targetPlayerId == monopolyGame->getPlayerOnTurn().getPlayerId())
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Enter valid player ID:";
					std::cin >> targetPlayerId;
					continue;
				}

				targetPlayer = &monopolyGame->getPlayer(targetPlayerId);

				trade = Trade(&monopolyGame->getPlayerOnTurn(), targetPlayer);

				std::cout << "\nWhat do you want to offer?" << std::endl;
				monopolyGame->printTradeOptions();

				std::cin >> offerType;

				while (std::cin.fail() || offerType < 1 || offerType > 4)
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Invalid option. Please choose 1, 2, 3 or 4: ";
					std::cin >> offerType;
				}

				std::cout << "You have successfully chosen option: " << offerType << std::endl;

				if (offerType == 1)
				{
					std::cout << "\nEnter amount of money to OFFER: ";
					std::cin >> offerMoney;

					while (std::cin.fail() || offerMoney < 0 || offerMoney > monopolyGame->getPlayerOnTurn().getMoney())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter appropriate money offer: ";
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
						if (monopolyGame->getPlayerOnTurn().getMyProperties()[i]->getrentLevel() <= 1
							&& monopolyGame->checkStreet(*monopolyGame->getPlayerOnTurn().getMyProperties()[i]))
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


						while (std::cin.fail()||offerPropIndex < 0 || offerPropIndex >= monopolyGame->getPlayerOnTurn().getMyProperties().size())
						{
							std::cin.clear();
							std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
							std::cout << "Enter valid index: ";
							std::cin >> offerPropIndex;
						}
						offerProperty = monopolyGame->getPlayerOnTurn().getMyProperties()[offerPropIndex];

						trade.setOfferedProperty(offerProperty);
					}
					else
					{
						std::cout << "You have no properties to trade." << std::endl;
						break;
					}
				}
				else if (offerType == 3)
				{
					std::cout << "Your train stations:" << std::endl;
					if (monopolyGame->getPlayerOnTurn().getMyStations().size() == 0)
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

					while (std::cin.fail() || offerPropIndex < 0 || offerPropIndex >= monopolyGame->getPlayerOnTurn().getMyStations().size())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter valid index: ";
						std::cin >> offerPropIndex;
					}
					offerTrainStation = monopolyGame->getPlayerOnTurn().getMyStations()[offerPropIndex];
					trade.setOfferedTrainStation(offerTrainStation);
				}
				else if (offerType == 4)
				{
					std::cout << "Your utilities:" << std::endl;
					if (monopolyGame->getPlayerOnTurn().getMyUtilities().size() == 0)
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

					while (std::cin.fail() || offerPropIndex < 0 || offerPropIndex >= monopolyGame->getPlayerOnTurn().getMyUtilities().size())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter valid index: ";
						std::cin >> offerPropIndex;
					}

					offerUtility = monopolyGame->getPlayerOnTurn().getMyUtilities()[offerPropIndex];
					trade.setOfferedCompanyField(offerUtility);
				}

				std::cout << "\nWhat do you want in return?" << std::endl;
				monopolyGame->printTradeOptions();

				std::cin >> requestType;

				while (std::cin.fail() || requestType < 1 || requestType > 4)
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Invalid option. Please choose 1, 2, 3 or 4: ";
					std::cin >> requestType;
					continue;
				}

				std::cout << "You have successfully chosen option: " << requestType << std::endl;

				if (requestType == 1)
				{
					std::cout << "\nEnter amount of money to REQUEST: ";
					std::cin >> requestMoney;

					while (std::cin.fail() || requestMoney < 0 || requestMoney > targetPlayer->getMoney())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter appropriate money request: ";
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
						if (targetPlayer->getMyProperties()[i]->getrentLevel() <= 1 && monopolyGame->checkStreet(*targetPlayer->getMyProperties()[i]))
						{
							std::cout << "  [" << i << "] " << targetPlayer->getMyProperties()[i]->getName() << std::endl;
							countValidTradeProperties++;
						}
					}
					if (countValidTradeProperties == 0)
					{
						std::cout << targetPlayer->getPlayerName() << " has no properties to trade." << std::endl;
						break;
					}
					std::cout << "Enter index of PROPERTY to REQUEST: ";
					std::cin >> requestPropIndex;

					Property* requestProp = nullptr;

					while (std::cin.fail() || requestPropIndex < 0 || requestPropIndex >= targetPlayer->getMyProperties().size())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter valid index: ";
						std::cin >> requestPropIndex;
					}
					requestProp = targetPlayer->getMyProperties()[requestPropIndex];

					trade.setRequestedProperty(requestProp);
				}
				else if (requestType == 3)
				{
					std::cout << targetPlayer->getPlayerName() << "'s train stations:" << std::endl;
					if (targetPlayer->getMyStations().size() == 0)
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

					while (std::cin.fail() || requestPropIndex < 0 || requestPropIndex >= targetPlayer->getMyStations().size())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter valid index: ";
						std::cin >> requestPropIndex;
					}

					requestTrainStation = targetPlayer->getMyStations()[requestPropIndex];
					trade.setRequestedTrainStation(requestTrainStation);
				}
				else if (requestType == 4)
				{
					std::cout << targetPlayer->getPlayerName() << "'s utilities:" << std::endl;
					if (targetPlayer->getMyUtilities().size() == 0)
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

					while (std::cin.fail()||requestPropIndex < 0 || requestPropIndex >= targetPlayer->getMyUtilities().size())
					{
						std::cin.clear();
						std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
						std::cout << "Enter valid index: ";
						std::cin >> requestPropIndex;			
					}
					requestUtility = targetPlayer->getMyUtilities()[requestPropIndex];
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
			}
			case 6:
			{
				std::cout << "[Mortgage a property]" << std::endl;

				monopolyGame->printMortgageMenu();

				owned = monopolyGame->getPlayerOnTurn().getMyProperties();

				if (owned.size()==0) 
				{
					std::cout << "You don't own any properties to mortgage." << std::endl;
					break;
				}

				mortgagedPropsCount = 0;

				std::cout << "Your available for mortgage properties:" << std::endl;

				for (size_t i = 0; i < owned.size(); i++) 
				{
					if (owned[i]->getrentLevel() <= 1&&monopolyGame->checkStreet(*owned[i]))
					{
						std::cout << i + 1 << ". " << owned[i]->getName()
							<< " (Price: " << owned[i]->getFieldPrice()
							<< ", Mortgaged: " << (owned[i]->getMortgaged() ? "Yes" : "No") << ")" << std::endl;
						mortgagedPropsCount++;
					}
				}

				if (mortgagedPropsCount == 0)
				{
					std::cout << "You don't have any valid properties for mortgage." << std::endl;
					break;
				}

				std::cout << "Enter the number of the property you want to mortgage: ";

				size_t choice;
				std::cin >> choice;

				while(std::cin.fail()|| choice < 1 || choice > owned.size())
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Enter valid property number: ";
					std::cin >> choice;
				}
				Property* selected = owned[choice - 1];

				if (selected->getMortgaged())
				{
					std::cout << "This property is already mortgaged." << std::endl;
					break;
				}

				selected->setMortgaged();
				mortgageValue = selected->getFieldPrice() / 2;
				monopolyGame->getPlayerOnTurn().addMoney(mortgageValue);

				std::cout << "You mortgaged " << selected->getName() << " for $" << mortgageValue << "." << std::endl;
				break;
			}
			case 7:
			{
				std::cout << "[Unmortgage]" << std::endl;

				mortgagedPropsCount = 0;

				owned = monopolyGame->getPlayerOnTurn().getMyProperties();

				if (owned.size() == 0)
				{
					std::cout << "You don't have any properties." << std::endl;
					break;
				}

				std::cout << "Your mortgaged properties:" << std::endl;

				for (size_t i = 0; i < owned.size(); i++)
				{
					if (owned[i]->getMortgaged())
					{
						std::cout << i + 1 << ". " << owned[i]->getName()
							<< " (Price: " << owned[i]->getFieldPrice()
							<< ", Mortgaged: " << (owned[i]->getMortgaged() ? "Yes" : "No") << ")" << std::endl;
						mortgagedPropsCount++;
					}
				}

				if (mortgagedPropsCount == 0)
				{
					std::cout << "You don't have mortgaged properties";
					break;
				}

				std::cout << "Enter the number of the property you want to unmortgage: ";

				size_t chooice;
				std::cin >> chooice;

				while (std::cin.fail() || chooice < 1 || chooice > owned.size())
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Enter valid property number: ";
					std::cin >> chooice;
				}

				mortgagedProps = owned[chooice - 1];

				if (!mortgagedProps->getMortgaged())
				{
					std::cout << "This property is already unmortgaged." << std::endl;
					break;
				}

				mortgagedProps->setMortgaged();
				mortgageValue = mortgagedProps->getFieldPrice() / 2;
				monopolyGame->getPlayerOnTurn().subtractMoney(mortgageValue);

				std::cout << "You unmortgaged " << mortgagedProps->getName() << " for $" << mortgageValue << "." << std::endl;
				break;
			}
			case 8:
			{
				std::cout << "[Sell Buildings]" << std::endl;

				std::vector<Property*> ownedWithBuildings;
				owned = monopolyGame->getPlayerOnTurn().getMyProperties();

				for (size_t i = 0; i < owned.size(); ++i)
				{
					if (owned[i]->getrentLevel() > 1)
					{
						std::cout << i << ". " << owned[i]->getName()<< " (Buildings: " << owned[i]->getrentLevel()-1 << ")" << std::endl;
						ownedWithBuildings.push_back(owned[i]);
					}
				}

				if (ownedWithBuildings.empty())
				{
					std::cout << "You have no buildings to sell." << std::endl;
					break;
				}

				std::cout << "Enter the number of the property you want to sell a house from: ";

				size_t sellChoice;
				std::cin >> sellChoice;

				while (std::cin.fail() || sellChoice >= owned.size() || sellChoice <0)
				{
					std::cin.clear();
					std::cin.ignore(GlobalConstants::INPUT_BUFFER_SIZE, '\n');
					std::cout << "Invalid choice. Try again: ";
					std::cin >> sellChoice;
				}

				Property* selectedProp = owned[sellChoice];

				bool canSell = true;

				for (int i=0;i<owned.size();i++)
				{
					if (owned[i]->getColor() == selectedProp->getColor() && owned[i] != selectedProp)
					{
						if (owned[i]->getrentLevel() > selectedProp->getrentLevel())
						{
							std::cout << "You must sell buildings evenly across properties of the same color." << std::endl;
							canSell = false;
							break;
						}
					}
				}
				
				if (!canSell)
				{
					break;
				}

				int sellPrice = selectedProp->getPriceForBuilding() / 2;

				std::cout << "You will receive $" << sellPrice << " for selling a house on "
					<< selectedProp->getName() << ". Proceed? (y/n): ";

				char confirm;
				std::cin >> confirm;

				if (confirm == 'y' || confirm == 'Y')
				{
					selectedProp->setRentLevel(selectedProp->getrentLevel()-1);
					monopolyGame->getPlayerOnTurn().addMoney(sellPrice);

					std::cout << "You sold a house on " << selectedProp->getName()
						<< " and received $" << sellPrice << "." << std::endl;
				}
				else
				{
					std::cout << "Sale cancelled." << std::endl;
				}

				break;
			}
			case 9:
			{
				std::cout << "[Exit GAME]" << std::endl;

				std::cout << "Are you sure you want to exit the game and give everything to the bank (y/n): ";

				char confirm;
				std::cin >> confirm;

				if (confirm == 'y' || confirm == 'Y')
				{
					turnEnded = true;

					monopolyGame->getPlayerOnTurn().bankrupt();

					newPlayerTurnIndex = monopolyGame->getPlayerOnTurn().getPlayerId() + 1;

					if (newPlayerTurnIndex >= monopolyGame->getPlayers().size())
					{
						newPlayerTurnIndex = 0;
					}

					monopolyGame->setCurrentTurnPlayerIndex(newPlayerTurnIndex);
				}
				else
				{
					std::cout << "Exit cancelled." << std::endl;
				}

				break;
			}
			case 10:
			{
				if (monopolyGame->getPlayerOnTurn().getIsInDebt())
				{
					turnEnded = false;
					std::cout << "Before you end you will have to pay your debt. (SELL STH)" << std::endl;
					std::cout << "Debt Amount: " << monopolyGame->getPlayerOnTurn().getDebtAmount() << std::endl;
					std::cout << std::endl;
					if (monopolyGame->getPlayerOnTurn().getMoney() >= monopolyGame->getPlayerOnTurn().getDebtAmount())
					{
						std::cout << "Do you want to pay your debt? (y/n) : ";
						char choice;
						std::cin >> choice;

						if (choice == 'y' || choice == 'Y')
						{
							turnEnded = true;
							monopolyGame->getPlayerOnTurn().subtractMoney(monopolyGame->getPlayerOnTurn().getDebtAmount());
							monopolyGame->getPlayerOnTurn().setDebtAmount(0);
							monopolyGame->getPlayerOnTurn().setDebt();
						}
						else
						{
							std::cout << "You chose not to pay." << std::endl;
							break;
						}
					}
					else
					{
						break;
					}
				}
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
			}
			case 11:
				saveToBinaryFile();
				monopolyGame->destroyInstance();
				return;
			default:
				std::cout << "Invalid option. Try again." << std::endl;
				break;
			}

		}
	}

	monopolyGame->printWinner();

	monopolyGame->destroyInstance();
}

void Engine::saveToBinaryFile() 
{
	std::ofstream ofs("monopoly_game.dat", std::ios::binary | std::ios::trunc);

	if (!ofs) {
		std::cerr << "Error opening file for saving." << std::endl;
		return;
	}

	ofs.write((const char*)(&rollDice), sizeof(rollDice));
	ofs.write((const char*)(&turnEnded), sizeof(turnEnded));

	monopolyGame->saveToBinary(ofs);

	ofs.close();
}

void Engine::loadFromBinaryFile()
{
	std::ifstream ifs("monopoly_game.dat", std::ios::binary);

	if (!ifs) {
		throw std::invalid_argument("No game saved. Please start a new one!");
	}

	ifs.read((char*)(&rollDice), sizeof(rollDice));
	ifs.read((char*)(&turnEnded), sizeof(turnEnded));

	monopolyGame->loadFromBinary(ifs);

	ifs.close();
}