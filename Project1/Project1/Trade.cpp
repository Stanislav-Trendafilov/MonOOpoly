#include "Trade.h"

Trade::Trade(Player& firstPlayer, Player& secondPlayer, int typeOfTrade, int requestType)
{
	this->firstPlayer = firstPlayer;
	this->secondPlayer = secondPlayer;
	this->typeOfTrade = typeOfTrade;
	this->requestType = requestType;
}

void Trade::applyTrade()
{
	if(typeOfTrade == 1)
	{ 
		int offerMoney;
		std::cout << "\nEnter amount of money to OFFER: ";
		std::cin >> offerMoney;

		while(offerMoney > firstPlayer.getMoney())
		{
			std::cout << "You don't have enough money." << std::endl;
			std::cin >> offerMoney;
		}
	}
	else if(typeOfTrade == 2) 
	{
	
	}
	else
	{
		
	}


}
