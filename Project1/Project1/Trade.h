#pragma once
#include <iostream>
#include "Player.h"

class Trade
{
	Player firstPlayer;
	Player secondPlayer;

	int typeOfTrade; 
	int requestType; 

public:
	Trade(Player&firstPlayer, Player& secondPlayer, int typeOfTrade,int requestType);

	void applyTrade();

};

