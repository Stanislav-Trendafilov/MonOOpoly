#include "Player.h"

Player::Player(const MyString& name, int money)
{
	this->playerName = name;
	this->money = money;
}

int Player::getMoney() const
{
	return money;
}
 
size_t Player::getCurrentPosition() const
{
	return currentPosition;
}

int Player::getTotalBalance() const
{
	return totalBalance;
}

bool Player::isJailed() const
{
	return isInPrison;
}
