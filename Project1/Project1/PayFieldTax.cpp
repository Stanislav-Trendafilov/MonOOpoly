#include "PayFieldTax.h"

PayFieldTax::PayFieldTax(const MyString& name, int boardIndex, int tax)		
	:Field(boardIndex,name)
{
	this->fieldTax = tax;
}

void PayFieldTax::ApplyAction(Player& player)
{
	player.subtractMoney(fieldTax);
}


Field* PayFieldTax::clone() const
{
	return new PayFieldTax(*this);
}
