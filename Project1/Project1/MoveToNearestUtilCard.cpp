#include "MoveToNearestUtilCard.h"
#include "Board.h"

MoveToNearestUtilCard::MoveToNearestUtilCard(const MyString& name, const MyString& effect)
	:Card(name, effect)
{
}

void MoveToNearestUtilCard::applyEffect(Player& player)
{
	size_t playerPosition = player.getCurrentPosition();

	for (size_t i = 0; i <= GlobalConstants::MAX_COUNT_FIELDS; i++)
	{
		if (playerPosition == GlobalConstants::FIELDS_RESTART_AT)
		{
			playerPosition = GlobalConstants::START_INDEX;
		}

		if (playerPosition == GlobalConstants::ELECTRIC_COMPANY_INDEX)
		{
			break;
		}
		else if (playerPosition == GlobalConstants::WATER_SUPPLY_INDEX)
		{
			break;
		}

		playerPosition++;

	}

	player.moveToLocation(playerPosition);
	Board::getInstance()->activateFieldEffect(player);


}

Card* MoveToNearestUtilCard::clone() const
{
	return new MoveToNearestUtilCard(*this);
}


