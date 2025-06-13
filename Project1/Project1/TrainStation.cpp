#include "TrainStation.h"
#include "CompanyField.h"


TrainStation::TrainStation(const MyString& name, size_t stationPrice, const int* rentPrices, int boardIndex)
 : Field(boardIndex,name)
{
	this->stationPrice = stationPrice;
	for (size_t i = 0; i < GlobalConstants::MAX_TRAIN_STATIONS; i++)
	{
		this->priceForRent[i] = rentPrices[i];
	}
	this->ownerId = -1;
	this->rentLevel = 0;
}

size_t TrainStation::getStationPrice() const
{
	return stationPrice;
}


int TrainStation::getRentLevel() const
{
	return rentLevel;
}


int TrainStation::getOwnerId() const
{
	return ownerId;
}

int TrainStation::getRentPrice() const
{
	return priceForRent[rentLevel];
}

Field* TrainStation::clone() const
{
	return new TrainStation(*this);
}
