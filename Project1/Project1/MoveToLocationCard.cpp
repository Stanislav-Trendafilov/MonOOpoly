#include "MoveToLocationCard.h"

MoveToLocationCard::MoveToLocationCard(const MyString& name, const MyString& effect, size_t indexOfLocation)
	:Card(name,effect)
{
	this->indexOfLocation = indexOfLocation;
}

void MoveToLocationCard::applyEffect(Player& player)	
{
	player.moveToLocation(indexOfLocation);
}

Card* MoveToLocationCard::clone() const
{
	return new MoveToLocationCard(*this);
}