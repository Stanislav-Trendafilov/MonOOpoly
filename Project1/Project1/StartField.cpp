#include "StartField.h"

StartField::StartField(const MyString& name, int boardIndex, int incomeTax)
	:Field(boardIndex, name)
{
	this->fieldIncome = incomeTax;
}

void StartField::ApplyAction(Player& player)
{
	player.addMoney(fieldIncome);
}

Field* StartField::clone() const
{
	return new StartField(*this);
}
