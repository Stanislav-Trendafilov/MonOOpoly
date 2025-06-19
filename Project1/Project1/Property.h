#pragma once
#include "Field.h"
#include "Player.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "Constants.h"

class Property:public Field
{
	size_t fieldPrice;
	size_t priceForBuilding;

	GlobalConstants::PropertyColors color;
	
	int priceForRent[GlobalConstants::MAX_BUILDINGS_PROPERTY];

	int rentLevel;

	int ownerId;

public:
	Property()=default;
	Property(const MyString& name, GlobalConstants::PropertyColors color, size_t fieldPrice, size_t priceForBuilding, const int* rentPrices,int boardIndex);

	size_t getFieldPrice() const;
	size_t getPriceForBuilding() const;
	int getrentLevel() const;
	int getOwnerId() const;
	int getRentPrice() const;
	GlobalConstants::PropertyColors getColor() const;

	void setRentLevel(int newLevel);
	void setOwnerId(int newOwnerId);
	void buildHouse();

	void ApplyAction(Player& player) override;

	Field* clone() const override;
};

 