#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(const MyString& name, const MyString& effect, size_t moveWith)
	:Card(name, effect)
{
	this->moveWith = moveWith;
}

void MovePositionCard::applyEffect(Player& player)
{
	//this information is hardcoded, so i Will put moveWith + or - , depending on the card type
	player.movePosition(moveWith);
}

Card* MovePositionCard::clone()const
{
	return new MovePositionCard(*this);
}
