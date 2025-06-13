#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(const MyString& name, const MyString& effect, size_t moveWith)
	:Card(name, effect)
{
	this->moveWith = moveWith;
}

void MovePositionCard::applyEffect(Player& player)
{
	player.movePosition(moveWith);
}

Card* MovePositionCard::clone()const
{
	return new MovePositionCard(*this);
}
