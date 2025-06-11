#pragma once
#include "MyString.h"

class Player
{
	int money;
	MyString playerName;
	size_t currentPosition;
	//totalBalance is money + price of all properties
	int totalBalance;
	bool isInPrison;

public:
	Player(const MyString& name, int money = 1500);

	int getMoney() const;
	size_t getCurrentPosition() const;
	int getTotalBalance() const;
	bool isJailed() const;

};

