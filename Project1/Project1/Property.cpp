#include "Property.h"
#include "Monopoly.h"

Property::Property(const MyString& name,GlobalConstants::PropertyColors color, size_t fieldPrice, size_t priceForBuilding, const int* rentPrices,int boardIndex)
	: Field(boardIndex,name)
{
	this->color = color;
	this->fieldPrice = fieldPrice;
	this->priceForBuilding = priceForBuilding;
	for (size_t i = 0; i < GlobalConstants::MAX_BUILDINGS_PROPERTY; i++)
	{
		this->priceForRent[i] = rentPrices[i];
	}
	this->ownerId = -1;
	this->rentLevel = 0;
}

size_t Property::getFieldPrice() const
{
	return fieldPrice;
}

size_t Property::getPriceForBuilding() const
{
	return priceForBuilding;
}

int Property::getrentLevel() const
{
	return rentLevel;
}

int Property::getOwnerId() const
{
	return ownerId;
}

int Property::getRentPrice() const
{
	return priceForRent[rentLevel];
}

void Property::ApplyAction(Player& player) 
{
   std::cout << "\n>>> You landed on property: " << getName() << " <<<"<<std::endl;

   if (ownerId == -1) 
   {
       std::cout << "This property is unowned." << std::endl;
       std::cout << "You can buy it for " << fieldPrice << "$."<<std::endl;
       std::cout << "Your current balance: $" << player.getMoney() << std::endl;

       if (player.getMoney() >= fieldPrice) 
       {
           std::cout << "Do you want to buy this property? (y/n): ";
           char choice;
           std::cin >> choice;

           if (choice == 'y' || choice == 'Y')
           {
               ownerId = player.getPlayerId();
               player.addProperty(this);
               std::cout << "You bought " << getName() << " successfully!" << std::endl;
           }
           else {
               std::cout << "You chose not to buy the property." << std::endl;
           }
       }
       else {
           std::cout << "You do not have enough money to buy this property." << std::endl;
       }

   }
   else if (ownerId != player.getPlayerId())
   {
       std::cout << "This property is owned by Player " << ownerId << "." << std::endl;

       int rent = getRentPrice();
       std::cout << "You must pay rent of " << rent << "$ ." << std::endl;;

       if (player.getMoney() >= rent) 
       {
           player.subtractMoney(rent);

           Player& ownerOfProperty = Monopoly::getInstance()->getPlayer(ownerId + 1); 
           ownerOfProperty.addMoney(rent);

		std::cout << "You paid " << rent << "$ rent to Player " << ownerOfProperty.getPlayerName() << "." << std::endl;
       }
       else
       {
		std::cout << "You do not have enough money to pay the rent!" << std::endl;
       }

   }
   else
   {
	std::cout << "You have landed on your property. Relax and see sth about OOP." << std::endl;
   }
}

Field* Property::clone() const
{
	return new Property(*this);
}
