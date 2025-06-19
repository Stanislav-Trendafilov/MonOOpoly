#include "Player.h"
#include "TrainStation.h"
#include "CompanyField.h"
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
	currentPosition = GlobalConstants::IN_JAIL_INDEX;
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

int Player::getLastRoll() const
{
	return lastRoll;
}

int Player::getTotalBalance() const
{
	return totalBalance;
}

MyVector<Property*> Player::getMyProperties() const
{
	return ownedProperties;
}

MyVector<TrainStation*> Player::getMyStations() const
{
	return ownedStations;
}

MyVector<CompanyField*> Player::getMyUtilities() const
{
	return ownedUtilities;
}

void Player::getOwnedProperties() const
{
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		std::cout << ownedProperties[i]->getName() << " -> Rent Level: " <<ownedProperties[i]->getrentLevel() <<std::endl;
	}
}

void Player::getOwnedStations() const
{
	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		std::cout << ownedStations[i]->getName() << " -> Rent Level: " << ownedStations[i]->getRentLevel() << std::endl;
	}
}

void Player::getOwnedUtilities() const
{
	for (size_t i = 0; i < ownedUtilities.size(); i++)
	{
		std::cout << ownedUtilities[i]->getName() << " -> Rent Level: " << ownedUtilities[i]->getUtilityCount() << std::endl;
	}
}

void Player::setRoll(int roll)
{
	lastRoll = roll;
}

void Player::addProperty(Property* property)
{	
	GlobalConstants::PropertyColors color = property->getColor();
	int countPropertiesOfColor = 0;

	bool getColorSet = false;

	if (!ownsProperty(property)) 
	{
		ownedProperties.push_back(property);
		for (size_t i = 0; i < ownedProperties.size(); i++)
		{
			if (ownedProperties[i]->getColor() == color)
			{
				countPropertiesOfColor++;
			}
			if(countPropertiesOfColor==2&& (color == GlobalConstants::PropertyColors::BROWN||color==GlobalConstants::PropertyColors::BLUE))
			{
				getColorSet = true;
			}
			else if(countPropertiesOfColor==3)
			{
				getColorSet = true;
			}
		}
		if(getColorSet)
		{
			std::cout << "You have all properties of color: " <<int(color) << std::endl;
			std::cout << "Now you will be able to build on them" << std::endl;
			for (size_t i = 0; i < ownedProperties.size(); i++)
			{
				if (ownedProperties[i]->getColor() == color)
				{
					
					ownedProperties[i]->setRentLevel(ownedProperties[i]->getrentLevel()+1);
				}
			}
		}

		money -= property->getFieldPrice();
		totalBalance += property->getFieldPrice(); // Обнови тотал баланса
	}

}

void Player::removeProperty(Property* property)
{

	GlobalConstants::PropertyColors color = property->getColor();
	//int countSameColor = 0;

	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i]->getColor() == color)
		{
			ownedProperties[i]->setRentLevel(0);
		}
	}

	//bool lostColorSet = false;
	//
	//if (color == GlobalConstants::PropertyColors::BROWN || color == GlobalConstants::PropertyColors::BLUE)
	//{
	//	if (countSameColor < 2)
	//	{
	//		lostColorSet = true;
	//	}
	//}
	//else
	//{
	//	if (countSameColor < 3)
	//	{
	//		lostColorSet = true;
	//	}
	//}
	//
	//if (lostColorSet)
	//{
	//	std::cout << "You lost the full color set of color: " << int(color) << std::endl;
	//	std::cout << "You are no longer allowed to build on that color." << std::endl;
	//
	//	for (size_t i = 0; i < ownedProperties.size(); ++i)
	//	{
	//		if (ownedProperties[i]->getColor() == color)
	//		{
	//			ownedProperties[i]->setRentLevel(0);
	//		}
	//	}
	//}

	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i] == property)
		{
			ownedProperties.remove(i);
			break;
		}
	}

	totalBalance -= property->getFieldPrice();

	property->setOwnerId(-1);

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

void Player::addStation(TrainStation* trainStation)
{
	ownedStations.push_back(trainStation);
	money -= trainStation->getStationPrice();
	totalBalance += trainStation->getStationPrice(); 

	trainStationCount++;

	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		ownedStations[i]->setRentLevel(trainStationCount-1);
	}
}

void Player::removeStation(TrainStation* trainStation)
{

	for (size_t i = 0; i < ownedStations.size(); i++)
	{

		if (trainStation->getName() == ownedStations[i]->getName())
		{
			trainStation->setRentLevel(0);
			ownedProperties.remove(i);
		}
	}

	trainStationCount--;

	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		ownedStations[i]->setRentLevel(trainStationCount-1);
	}
}

void Player::addUtility(CompanyField* company)
{
	ownedUtilities.push_back(company);
	money -= company->getCompanyPrice();
	totalBalance += company->getCompanyPrice();
							 
	utilitiesCount++;

	company->setUtilityCount(utilitiesCount);
}

void Player::removeUtility(CompanyField* company)
{
	for (size_t i = 0; i < ownedUtilities.size(); i++)
	{
		if (company->getName() == ownedUtilities[i]->getName())
		{
			company->setUtilityCount(0);
			ownedUtilities.remove(i);
		}

	}

	utilitiesCount--;

	for (size_t i = 0; i < ownedUtilities.size(); i++)
	{
		ownedUtilities[i]->setUtilityCount(utilitiesCount);
	}
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
		addMoney(GlobalConstants::PASS_START_CASH);
	}

}

void Player::moveToLocation(size_t position)
{
	currentPosition = position;
	if (currentPosition > GlobalConstants::MAX_COUNT_FIELDS)
	{
		currentPosition -= 40;
		addMoney(GlobalConstants::PASS_START_CASH);
	}
}

bool Player::isJailed() const
{
	return isInPrison;
}