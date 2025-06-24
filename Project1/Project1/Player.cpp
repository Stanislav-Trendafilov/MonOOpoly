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
	return totalBalance+money;
}

int Player::getRoundsInPrison() const
{
	return roundsInPrison;
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

bool Player::ownsIndex(int index) const
{
	bool ownsId = false;
	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i]->getFieldId() == index)
		{
			ownsId = true;
			return ownsId;
		}
	}
	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		if (ownedStations[i]->getFieldId() == index)
		{
			ownsId = true;
			return ownsId;
		}
	}
	for (size_t i = 0; i < ownedUtilities.size(); i++)
	{
		if (ownedUtilities[i]->getFieldId() == index)
		{
			ownsId = true;
			return ownsId;
		}
	}
	
	return ownsId;
}

void Player::setRoll(int roll)
{
	lastRoll = roll;
}

void Player::setRoundInPrison(int rounds)
{
	this->roundsInPrison = rounds;
}

void Player::addProperty(Property* property)
{	
	GlobalConstants::PropertyColors color = property->getColor();
	int countPropertiesOfColor = 0;

	bool getColorSet = false;

	if (!ownsProperty(property)) 
	{
		ownedProperties.push_back(property);
		property->setOwnerId(playerId);
		for (size_t i = 0; i < ownedProperties.size(); i++)
		{
			if (ownedProperties[i]->getColor() == color)
			{
				countPropertiesOfColor++;
			}
			if(countPropertiesOfColor==2 && (color == GlobalConstants::PropertyColors::BROWN||color==GlobalConstants::PropertyColors::BLUE))
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
				if (ownedProperties[i]->getColor() == color&& ownedProperties[i]->getrentLevel()==0)
				{
					ownedProperties[i]->setRentLevel(ownedProperties[i]->getrentLevel()+1);
				}
			}
		}

		money -= property->getFieldPrice();
		totalBalance += (property->getFieldPrice()/2); 
	}

}

void Player::removeProperty(Property* property)
{

	GlobalConstants::PropertyColors color = property->getColor();

	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i]->getColor() == color)
		{
			ownedProperties[i]->setRentLevel(0);
		}
	}

	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		if (ownedProperties[i] == property)
		{
			ownedProperties.remove(i);
			break;
		}
	}

	totalBalance -= property->getFieldPrice()/2;

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
	trainStation->setOwnerId(playerId);
	money -= trainStation->getStationPrice();
	totalBalance += (trainStation->getStationPrice()/2); 

	trainStationCount++;

	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		ownedStations[i]->setRentLevel(trainStationCount-1);
	}
}

void Player::removeStation(TrainStation* trainStation)
{
	totalBalance -= (trainStation->getStationPrice() / 2);

	for (size_t i = 0; i < ownedStations.size(); i++)
	{

		if (trainStation->getName() == ownedStations[i]->getName())
		{
			trainStation->setRentLevel(0);
			ownedStations.remove(i);
		}
	}

	trainStationCount--;

	for (size_t i = 0; i < ownedStations.size(); i++)
	{
		ownedStations[i]->setRentLevel(trainStationCount-1);
	}

	trainStation->setOwnerId(-1);

}

void Player::addUtility(CompanyField* company)
{
	ownedUtilities.push_back(company);
	company->setOwnerId(playerId);
	money -= company->getCompanyPrice();
	totalBalance += (company->getCompanyPrice()/2);
							 
	utilitiesCount++;

	for (size_t i = 0; i < ownedUtilities.size(); i++)
	{
		ownedUtilities[i]->setUtilityCount(utilitiesCount);
	}
}

void Player::removeUtility(CompanyField* company)
{
	totalBalance += (company->getCompanyPrice() / 2);

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

	company->setOwnerId(-1);
}

void Player::addMoney(int amount)
{
	money += amount;
}

void Player::subtractMoney(int amount)
{
	if (money - amount < 0)
	{
		std::cout << playerName << " don't have enough money and have to sell sth" << std::endl;
		isInDebt = true;
		debtMoney = amount;
	}
	else
	{
		money -= amount;
	}
}

void Player::movePosition(size_t steps)
{
															  
	currentPosition += steps;
	if (currentPosition > GlobalConstants::MAX_COUNT_FIELDS)
	{
		currentPosition -= GlobalConstants::FIELDS_RESTART_AT;
		addMoney(GlobalConstants::PASS_START_CASH);
	}

}

void Player::moveToLocation(size_t position)
{
	currentPosition = position;
	if (currentPosition > GlobalConstants::MAX_COUNT_FIELDS)
	{
		currentPosition -= GlobalConstants::FIELDS_RESTART_AT;
		addMoney(GlobalConstants::PASS_START_CASH);
	}
}

bool Player::isJailed() const
{
	return isInPrison;
}

bool Player::getIsInDebt() const
{
	return isInDebt;
}

void Player::setDebt() 
{
	if (isInDebt)
	{
		isInDebt = false;
	}
	else
	{
		isInDebt = true;
	}

}

int Player::getDebtAmount() const
{
	return debtMoney;
}

void Player::setDebtAmount(int debtAmount)
{
	debtMoney = debtAmount;
}

void Player::bankrupt()
{
	int propSize = ownedProperties.size();
	for (int i = propSize - 1; i >= 0; i--)
	{
		ownedProperties[i]->setRentLevel(0);
	}
	for (int i = propSize - 1; i >= 0; i--)
	{
		removeProperty(ownedProperties[i]);
	}

	int stationsCount = ownedStations.size();
	for (int i = stationsCount - 1; i >= 0; i--)
	{
		removeStation(ownedStations[i]);
	}

	int companiesCount = ownedUtilities.size();
	for (int i = companiesCount - 1; i >= 0; i--)
	{
		removeUtility(ownedUtilities[i]);
	}
	
	leftGame();
}

bool Player::getIsInGame()	const
{
	return isInGame;
}

void Player::leftGame()
{
	isInGame = false;
}

void Player::saveToBinary(std::ofstream& ofs) const
{
	ofs.write((const char*)(&playerId), sizeof(playerId));
	ofs.write((const char*)(&money), sizeof(money));
	ofs.write((const char*)(&totalBalance), sizeof(totalBalance));
	ofs.write((const char*)(&debtMoney), sizeof(debtMoney));

	int size = playerName.length();
	ofs.write((const char*)(&size), sizeof(size));
	ofs.write(playerName.c_str(), sizeof(char) * size);;

	ofs.write((const char*)(&currentPosition), sizeof(currentPosition));
	//ofs.write((const char*)(&trainStationCount), sizeof(trainStationCount));
	//ofs.write((const char*)(&utilitiesCount), sizeof(utilitiesCount));
	ofs.write((const char*)(&lastRoll), sizeof(lastRoll));
	ofs.write((const char*)(&roundsInPrison), sizeof(roundsInPrison));

	ofs.write((const char*)(&isInPrison), sizeof(isInPrison));
	ofs.write((const char*)(&isInDebt), sizeof(isInDebt));
	ofs.write((const char*)(&isInGame), sizeof(isInGame));

}

void Player::loadFromBinary(std::ifstream& ifs)
{

	ifs.read((char*)(&playerId), sizeof(playerId));
	ifs.read((char*)(&money), sizeof(money));
	ifs.read((char*)(&totalBalance), sizeof(totalBalance));
	ifs.read((char*)(&debtMoney), sizeof(debtMoney));

	int size = 0;
	ifs.read((char*)(&size), sizeof(size));
	char* buffer = new char[size + 1];
	ifs.read(buffer, sizeof(char) * size);
	buffer[size] = '\0';
	playerName=buffer;
	delete[] buffer;

	ifs.read((char*)(&currentPosition), sizeof(currentPosition));
	//ifs.read((char*)(&trainStationCount), sizeof(trainStationCount));
	//ifs.read((char*)(&utilitiesCount), sizeof(utilitiesCount));
	ifs.read((char*)(&lastRoll), sizeof(lastRoll));
	ifs.read((char*)(&roundsInPrison), sizeof(roundsInPrison));

	ifs.read((char*)(&isInPrison), sizeof(isInPrison));
	ifs.read((char*)(&isInDebt), sizeof(isInDebt));
	ifs.read((char*)(&isInGame), sizeof(isInGame));
}