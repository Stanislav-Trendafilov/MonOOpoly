#include "Trade.h"
#include <iostream>

Trade::Trade()
{
}

Trade::Trade(Player* first, Player* second)
{
	this->firstPlayer = first;
	this->secondPlayer = second;
}

void Trade::setOfferedMoney(int money)
{
	this->offeredMoney = money;
}

void Trade::setRequestedMoney(int money)
{
	this->requestedMoney = money;
}

void Trade::setOfferedProperty(Property* property)
{
	this->offeredProperty = property;
}

void Trade::setRequestedProperty(Property* property)
{
	this->requestedProperty = property;
}

void Trade::showTradeOffer() 
{
	std::cout << "\n-------> Trade Offer <-------" << std::endl;
	std::cout << firstPlayer->getPlayerName() << " offers:" << std::endl;

	if (offeredMoney > 0)
	{
		std::cout << "  Money: $" << offeredMoney << std::endl;
	}
	if(offeredProperty!= nullptr)
	{
		std::cout << "  Property: " << offeredProperty->getName() << std::endl;
	}
	std::cout << "\nIn return for:"<< std::endl;

	if (requestedMoney > 0)
	{
		std::cout << "  Money: $" << requestedMoney << std::endl;
	}
	if(requestedProperty != nullptr)
	{
		std::cout << "  Property: " << requestedProperty->getName() << std::endl;
	}
	std::cout << "-----------------------------" << std::endl;
}

void Trade::applyTrade()
{
	if (offeredMoney > 0)
	{
		firstPlayer->subtractMoney(offeredMoney);
		secondPlayer->addMoney(offeredMoney);
	}
	if (requestedMoney > 0)
	{
		secondPlayer->subtractMoney(requestedMoney);
		firstPlayer->addMoney(requestedMoney);
	}

	if (offeredProperty!=nullptr)
	{
		firstPlayer->removeProperty(offeredProperty);
		secondPlayer->addProperty(offeredProperty);
		secondPlayer->addMoney(offeredProperty->getFieldPrice()); 
	}
	
	if (requestedProperty != nullptr)
	{
		secondPlayer->removeProperty(requestedProperty);
		firstPlayer->addProperty(requestedProperty);
		firstPlayer->addMoney(requestedProperty->getFieldPrice());
	}

	std::cout << "Trade successfully completed."<< std::endl;
}


