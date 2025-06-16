#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Property.h"
#include "Constants.h"

class Player
{
	int money;
	int ownerId;
	MyString playerName;
	size_t currentPosition;
	MyVector<Property> ownedProperties;

	size_t trainStationCount;
	int totalBalance; //totalBalance is money + price of all properties
	bool isInPrison;

public:
	Player();
	Player(const MyString& name, int money = GlobalConstants::STARTING_CASH);

	int getMoney() const;
	size_t getCurrentPosition() const;
	size_t getTrainStationCount() const;
	int getTotalBalance() const;

	void addProperty(const Property* property);
	void removeProperty(const Property* property);
	bool ownsProperty(Property* property) const;
	void addMoney(int amount);
	void subtractMoney(int amount);
	void movePosition(size_t steps);
	void moveToLocation(size_t locationIndex);

	void goInPrison();
	void goOutOfPrison();
	bool isJailed() const;

};

