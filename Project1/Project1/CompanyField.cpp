#include "CompanyField.h"

CompanyField::CompanyField(const MyString& name, size_t companyPrice, const int* rentPrices, int boardIndex)
	: Field(boardIndex,name)
{
	this->companyPrice = companyPrice;
	for (int i = 0; i < 6; ++i) {
		this->priceForRent[i] = rentPrices[i];
	}
}

size_t CompanyField::getCompanyPrice() const
{
	return companyPrice;
}

int CompanyField::getOwnerId() const
{
	return ownerId;
}

int CompanyField::getRentLevel() const
{
	return rentLevel;
}

Field* CompanyField::clone() const
{
	return new CompanyField(*this);
}
