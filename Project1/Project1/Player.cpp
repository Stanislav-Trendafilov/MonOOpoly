#include "Player.h"

Player::Player(const MyString& name, int money)
{
	this->playerName = name;
	this->money = money;
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

void Player::addProperty(const Property* property)
{
	ownedProperties.push_back(*property);
	money -= property->getFieldPrice();
	totalBalance += property->getFieldPrice()/2;
}

void Player::removeProperty(const Property* property)
{
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (property->getName() == ownedProperties[i].getName())
		{
			ownedProperties.remove(i);
	   }
	}
}

bool Player::ownsProperty(Property* property) const
{
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i].getName()==property->getName())
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

bool Player::isJailed() const
{
	return isInPrison;
}
