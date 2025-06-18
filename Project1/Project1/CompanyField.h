#pragma once
#include "Field.h"
#include "Constants.h"


class CompanyField :public Field
{
	size_t companyPrice;

	int utilityCount;

	int ownerId=-1;


public:
	CompanyField(const MyString& name, size_t companyPrice,int boardIndex);

	size_t getCompanyPrice() const;

	int getUtilityCount() const;
	int getOwnerId() const;
	int getRentPrice() const;

	void setUtilityCount  (int level);

	void ApplyAction(Player& player) override;	

	Field* clone() const override;
};

