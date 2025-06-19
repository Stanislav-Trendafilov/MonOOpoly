#pragma once
#include <iostream>
#include "Player.h"
#include "Property.h"
#include "TrainStation.h"
#include "CompanyField.h"

class Trade
{
	Player* firstPlayer;
	Player* secondPlayer; 

	int offeredMoney = 0;
	int requestedMoney = 0;

	Property* offeredProperty = nullptr;
	Property* requestedProperty = nullptr;

	TrainStation* offeredTrainStation = nullptr;
	TrainStation* requestedTrainStation = nullptr;

	CompanyField* offeredCompanyField = nullptr;
	CompanyField* requestedCompanyField = nullptr;

public:
	Trade();
	Trade(Player* first, Player* second);

	void setOfferedMoney(int money);
	void setRequestedMoney(int money);

	void setOfferedProperty(Property* property);
	void setRequestedProperty(Property* property);

	void setOfferedTrainStation(TrainStation* trainStation);
	void setRequestedTrainStation(TrainStation* trainStation);

	void setOfferedCompanyField(CompanyField* companyField);
	void setRequestedCompanyField(CompanyField* companyField);

	void applyTrade(); 
	void showTradeOffer();
};

