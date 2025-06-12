#pragma once
#include "Field.h"
#include "MyString.h"
#include "Constants.h"

class Property:public Field
{
	MyString name;

	size_t fieldPrice;
	size_t priceForBuilding;

	GlobalConstants::PropertyColors color;
	
	int priceForRent[GlobalConstants::MAX_BUILDINGS_PROPERTY];

	int rentLevel;

	int ownerId;

public:
	Property()=default;
	Property(const MyString& name, GlobalConstants::PropertyColors color, size_t fieldPrice, size_t priceForBuilding, const int* rentPrices,int boardIndex);
	MyString getName() const;
	size_t getFieldPrice() const;
	size_t getPriceForBuilding() const;
	int getrentLevel() const;
	int getOwnerId() const;
	int getRentPrice() const;
	Field* clone() const override;
};

 