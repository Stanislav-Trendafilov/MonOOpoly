#pragma once
#include "MyString.h"
#include "Constants.h"
class Player
{
	int money;
	int ownerId;
	MyString playerName;
	size_t currentPosition;
	//totalBalance is money + price of all properties

	int totalBalance;
	bool isInPrison;

public:
	Player(const MyString& name, int money = GlobalConstants::STARTING_CASH);

	int getMoney() const;
	size_t getCurrentPosition() const;
	int getTotalBalance() const;
	bool isJailed() const;

};

