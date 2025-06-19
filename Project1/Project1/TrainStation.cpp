#include "TrainStation.h"
#include "Monopoly.h"

TrainStation::TrainStation(const MyString& name, size_t stationPrice, const int* rentPrices, int boardIndex)
 : Field(boardIndex,name)
{
	this->stationPrice = stationPrice;
	for (size_t i = 0; i < GlobalConstants::MAX_TRAIN_STATIONS; i++)
	{
		this->priceForRent[i] = rentPrices[i];
	}
	this->ownerId = -1;
	this->rentLevel = 0;
}

size_t TrainStation::getStationPrice() const
{
	return stationPrice;
}

int TrainStation::getRentLevel() const
{
	return rentLevel;
}

int TrainStation::getOwnerId() const
{
	return ownerId;
}

int TrainStation::getRentPrice() const
{
	return priceForRent[rentLevel];
}

void TrainStation::setRentLevel(int level)
{
	rentLevel = level;
}

void TrainStation::ApplyAction(Player& player)
{
    std::cout << "\n>>> You landed on: " << getName() << " <<<" << std::endl;

    if (ownerId == -1)
    {
        std::cout << "This train station is unowned." << std::endl;
        std::cout << "You can buy it for " << stationPrice << "$." << std::endl;
        std::cout << "Your current balance: $" << player.getMoney() << std::endl;

        if (player.getMoney() >= stationPrice)
        {
            std::cout << "Do you want to buy this station? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                ownerId = player.getPlayerId();
                player.addStation(this);
                std::cout << "You bought " << getName() << " successfully!" << std::endl;
            }
            else {
                std::cout << "You chose not to buy the station." << std::endl;
            }
        }
        else {
            std::cout << "You do not have enough money to buy this station." << std::endl;
        }

    }
    else if (ownerId != player.getPlayerId())
    {
        std::cout << "This station is owned by Player " << ownerId << "." << std::endl;

        int rent = getRentPrice();
        std::cout << "You must pay rent of " << rent << "$ ." << std::endl;;

        if (player.getMoney() >= rent)
        {
            player.subtractMoney(rent);

            Player& ownerOfProperty = Monopoly::getInstance()->getPlayer(ownerId);
            ownerOfProperty.addMoney(rent);

            std::cout << "You paid " << rent << "$ rent to Player " << ownerOfProperty.getPlayerName() << "." << std::endl;
        }
        else
        {
            std::cout << "You do not have enough money to pay the rent!" << std::endl;
        }

    }
    else
    {
        std::cout << "You have landed on your station. Relax and see sth about OOP." << std::endl;
    }
}

Field* TrainStation::clone() const
{
	return new TrainStation(*this);
}
