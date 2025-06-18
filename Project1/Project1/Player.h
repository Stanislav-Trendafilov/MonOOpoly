#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Constants.h"

class Property;	   
class TrainStation;
class CompanyField;

class Player
{
	int money;
	int playerId;
	MyString playerName;
	size_t currentPosition;
	MyVector<Property*> ownedProperties;
	MyVector<TrainStation*> ownedStations;
	MyVector<CompanyField*> ownedUtilities; 

	size_t trainStationCount=0;// rent [0 1 2 3] [50 100 150 200]
	size_t utilitiesCount = 0;

	int lastRoll; //lastRoll is the last dice roll of the player (utility logic)
	int totalBalance; //totalBalance is money + price of all properties
	bool isInPrison;

public:
	Player();
	Player(int playerId,const MyString& name, int money = GlobalConstants::STARTING_CASH);

	int getPlayerId() const;	
	int getMoney() const;
	MyString getPlayerName() const;
	size_t getCurrentPosition() const;
	size_t getTrainStationCount() const;
	int getLastRoll() const;
	int getTotalBalance() const;	   
	void getOwnedProperties() const;
	void getOwnedStations() const;
	
	void setRoll(int roll);

	void addProperty(Property* property);
	void removeProperty(Property* property);
	bool ownsProperty(Property* property) const;

	void addStation(TrainStation* trainStation);
	void removeStation(TrainStation* trainStation);

	void addUtility(CompanyField* company);
	void removeUtility(CompanyField* company);
	
	void addMoney(int amount);
	void subtractMoney(int amount);
	void movePosition(size_t steps);
	void moveToLocation(size_t locationIndex);

	void goInPrison();
	void goOutOfPrison();
	bool isJailed() const;

};

