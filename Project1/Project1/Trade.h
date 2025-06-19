#pragma once
#include <iostream>
#include "Player.h"
#include "Property.h"

class Trade
{
	Player* firstPlayer;
	Player* secondPlayer; 

	int offeredMoney = 0;
	int requestedMoney = 0;

	Property* offeredProperty = nullptr;
	Property* requestedProperty = nullptr;

public:
	Trade();
	Trade(Player* first, Player* second);

	void setOfferedMoney(int money);
	void setRequestedMoney(int money);

	void setOfferedProperty(Property* property);
	void setRequestedProperty(Property* property);

	void applyTrade(); 
	void showTradeOffer();
};

