#include "PayFieldTax.h"

PayFieldTax::PayFieldTax(const MyString& name, int boardIndex, int tax)		
	:Field(boardIndex,name)
{
	this->fieldTax = tax;
}

void PayFieldTax::ApplyAction(Player& player)
{
	std::cout << "You have landed on a "<<this->getName()<<" field." << std::endl;
	std::cout << "You have to pay a tax of " << fieldTax << " to the bank." << std::endl;
	player.subtractMoney(fieldTax);
}

Field* PayFieldTax::clone() const
{
	return new PayFieldTax(*this);
}
