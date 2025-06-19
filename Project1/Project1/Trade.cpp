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

void Trade::setOfferedTrainStation(TrainStation* trainStation)
{
	this->offeredTrainStation = trainStation;
}

void Trade::setRequestedTrainStation(TrainStation* trainStation)
{
	this->requestedTrainStation = trainStation;
}

void Trade::setOfferedCompanyField(CompanyField* companyField)
{
	this->offeredCompanyField = companyField;
}

void Trade::setRequestedCompanyField(CompanyField* companyField)
{
	this->requestedCompanyField = companyField;
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
	if (offeredTrainStation != nullptr)
	{
		std::cout << "  Train Station: " << offeredTrainStation->getName() << std::endl;
	}
	if( offeredCompanyField != nullptr)
	{
		std::cout << "  Company Field: " << offeredCompanyField->getName() << std::endl;
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
	if (requestedTrainStation != nullptr)
	{
		std::cout << "  Train Station: " << requestedTrainStation->getName() << std::endl;
	}
	if (requestedCompanyField != nullptr)
	{
		std::cout << "  Company Field: " << requestedCompanyField->getName() << std::endl;
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

	if (offeredTrainStation != nullptr)
	{
		firstPlayer->removeStation(offeredTrainStation);
		secondPlayer->addStation(offeredTrainStation);
		secondPlayer->addMoney(offeredTrainStation->getStationPrice());
	}

	if (requestedTrainStation != nullptr)
	{
		secondPlayer->removeStation(requestedTrainStation);
		firstPlayer->addStation(requestedTrainStation);
		firstPlayer->addMoney(requestedTrainStation->getStationPrice());
	}

	if (offeredCompanyField != nullptr)
	{
		firstPlayer->removeUtility(offeredCompanyField);
		secondPlayer->addUtility(offeredCompanyField);
		secondPlayer->addMoney(offeredCompanyField->getCompanyPrice());
	}

	if (requestedCompanyField != nullptr)
	{
		secondPlayer->removeUtility(requestedCompanyField);
		firstPlayer->addUtility(requestedCompanyField);
		firstPlayer->addMoney(requestedCompanyField->getCompanyPrice());
	}
	std::cout << "Trade successfully completed."<< std::endl;
}


