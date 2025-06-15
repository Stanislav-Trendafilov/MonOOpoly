#pragma once
#include "Field.h"
#include "Constants.h"

class CompanyField :public Field
{
	size_t companyPrice;

	int priceForRent[GlobalConstants::MAX_COMPANIES];

	int rentLevel;

	int ownerId;

public:
	CompanyField(const MyString& name, size_t companyPrice, const int* rentPrices, int boardIndex);

	size_t getCompanyPrice() const;

	int getRentLevel() const;
	int getOwnerId() const;
	int getRentPrice() const;

	void ApplyAction(Player& player) override;	

	Field* clone() const override;
};

