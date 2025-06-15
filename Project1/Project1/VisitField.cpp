#include "VisitField.h"

VisitField::VisitField(int index, MyString name)
	: Field(index, name)
{
}

void VisitField::ApplyAction(Player& player)
{
	std::cout << "You have landed on visit field. Just relax :) "<< std::endl;
}

Field* VisitField::clone() const
{
	return new VisitField(*this);
}
