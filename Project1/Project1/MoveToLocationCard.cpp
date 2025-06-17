#include "MoveToLocationCard.h"
#include "Board.h"

MoveToLocationCard::MoveToLocationCard(const MyString& name, const MyString& effect, size_t indexOfLocation)
	:Card(name,effect)
{
	this->indexOfLocation = indexOfLocation;
}

void MoveToLocationCard::applyEffect(Player& player)	
{
	int movement = indexOfLocation- player.getCurrentPosition();
	if (movement < 0)
	{
		movement = (-1)*movement;
	}
	if(player.getCurrentPosition()+movement>GlobalConstants::MAX_COUNT_FIELDS && indexOfLocation!=GlobalConstants::JAIL_INDEX)
	{
		player.addMoney(GlobalConstants::PASS_START_CASH);
	}
	player.moveToLocation(indexOfLocation);
	Board::getInstance()->activateFieldEffect(player);
}

Card* MoveToLocationCard::clone() const
{
	return new MoveToLocationCard(*this);
}