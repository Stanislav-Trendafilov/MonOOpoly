#pragma once
#include "Field.h"
#include "Player.h"
#include "MyString.h"
#include "Constants.h"

class TrainStation :public Field
{

	size_t stationPrice;

	int priceForRent[GlobalConstants::MAX_TRAIN_STATIONS];

	int rentLevel;

	int ownerId;

public:
	TrainStation(const MyString& name, size_t stationPrice, const int* rentPrices, int boardIndex);

	size_t getStationPrice() const;

	int getRentLevel() const;
	int getOwnerId() const;
	int getRentPrice() const;

	void setRentLevel(int level);

	void ApplyAction(Player& player) override;

	Field* clone() const override;
};


