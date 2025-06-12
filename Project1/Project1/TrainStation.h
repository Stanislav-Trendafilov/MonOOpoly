#pragma once
#include "Field.h"
#include "MyString.h"
#include "Constants.h"

class TrainStation :public Field
{
	MyString name;

	size_t stationPrice;

	int priceForRent[GlobalConstants::MAX_TRAIN_STATIONS];

	int rentLevel;

	int ownerId;

public:
	TrainStation(const MyString& name, size_t stationPrice, const int* rentPrices, int boardIndex);
	MyString getName() const;
	size_t getstationPricePrice() const;

	int getRentLevel() const;
	int getOwnerId() const;
	int getRentPrice() const;

	Field* clone() const override;


};


