#include "Property.h"



Property::Property(const MyString& name,GlobalConstants::PropertyColors color, size_t fieldPrice, size_t priceForBuilding, const int* rentPrices,int boardIndex)
	: Field(boardIndex)
{
	this->name = name;
	this->color = color;
	this->fieldPrice = fieldPrice;
	this->priceForBuilding = priceForBuilding;
	for (size_t i = 0; i < GlobalConstants::MAX_BUILDINGS_PROPERTY; i++)
	{
		this->priceForRent[i] = rentPrices[i];
	}
	this->ownerId = -1;
	this->rentLevel = 0;
}
MyString Property::getName() const
{
	return name;
}
;

size_t Property::getFieldPrice() const
{
	return fieldPrice;
}

size_t Property::getPriceForBuilding() const
{
	return priceForBuilding;
}

int Property::getrentLevel() const
{
	return rentLevel;
}

int Property::getOwnerId() const
{
	return ownerId;
}

int Property::getRentPrice() const
{
	return priceForRent[rentLevel];
}

Field* Property::clone() const
{
	return new Property(*this);
}
