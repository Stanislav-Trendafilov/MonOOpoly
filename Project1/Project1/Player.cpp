#include "Player.h"
#include "Property.h"

Player::Player()
{
}

Player::Player(int playerId, const MyString& name, int money)
{
	this->playerId = playerId;
	this->playerName = name;
	this->money = money;
}

int Player::getPlayerId() const
{
	return playerId;
}

void Player::goInPrison()
{
	isInPrison = true;
}

void Player::goOutOfPrison()
{
	isInPrison = false;
}

int Player::getMoney() const
{
	return money;
}

MyString Player::getPlayerName() const
{
	return playerName;
}
 
size_t Player::getCurrentPosition() const
{
	return currentPosition;
}

size_t Player::getTrainStationCount() const
{
	return trainStationCount;
}

int Player::getTotalBalance() const
{
	return totalBalance;
}

void Player::addProperty(Property* property)
{
	if (!ownsProperty(property)) {
		ownedProperties.push_back(property);
		money -= property->getFieldPrice();
		totalBalance += property->getFieldPrice(); // Обнови тотал баланса
	}
}

void Player::removeProperty(Property* property)
{
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (property->getName() == ownedProperties[i]->getName())
		{
			ownedProperties.remove(i);
		}
	}
}

bool Player::ownsProperty(Property* property) const
{
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i]->getName() == property->getName())
		{
			return true;
		}
	}
	return false;
}

void Player::addMoney(int amount)
{
	money += amount;
}

void Player::subtractMoney(int amount)
{
	money -= amount;
}

void Player::movePosition(size_t steps)
{
	currentPosition += steps;
	if (currentPosition > GlobalConstants::MAX_COUNT_FIELDS)
	{
		currentPosition -= 40; 
	}
}

void Player::moveToLocation(size_t position)
{
	currentPosition = position;
}

bool Player::isJailed() const
{
	return isInPrison;
}
