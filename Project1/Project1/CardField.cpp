#include "CardField.h"

CardField::CardField(const MyString& name, size_t boardIndex)
	: Field(boardIndex,name)
{
	//this->deck = cards;
}

void CardField::DrawChanceCard(Player& player)
{
}

void CardField::DrawCommunityCard(Player& player)
{
}

void CardField::ApplyAction(Player& player)
{	
}

Field* CardField::clone() const
{
	return new CardField(*this);
}

