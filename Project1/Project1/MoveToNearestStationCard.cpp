#include "MoveToNearestStationCard.h"
#include "Board.h"

MoveToNearestStationCard::MoveToNearestStationCard(const MyString& name, const MyString& effect)
	: Card(name, effect) 
{
}

void MoveToNearestStationCard::applyEffect(Player& player) 
{
	size_t playerPosition = player.getCurrentPosition();

	for (size_t i = 0; i <= GlobalConstants::MAX_COUNT_FIELDS; i++)
	{
		if (playerPosition == GlobalConstants::FIELDS_RESTART_AT)
		{
			playerPosition = GlobalConstants::START_INDEX;
		}

		if (playerPosition == GlobalConstants::TRAINSTATION1_INDEX)
		{
			break;
		}
		else if (playerPosition == GlobalConstants::TRAINSTATION2_INDEX)
		{
			break;
		}
		else if (playerPosition == GlobalConstants::TRAINSTATION3_INDEX)
		{
			break;
		}
		else if (playerPosition == GlobalConstants::TRAINSTATION4_INDEX)
		{
			break;
		}
		playerPosition++;

	}
	player.moveToLocation(playerPosition);
	 
	Board::getInstance()->activateFieldEffect(player);


}
Card* MoveToNearestStationCard::clone() const
{
	return new MoveToNearestStationCard(*this);
}
