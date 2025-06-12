#include <iostream>
#include "Player.h"
#include "Property.h"
#include "MyString.h"
#include "Constants.h"
#include "Board.h"

int main(){

	MyString name = "street1";

	int rent[] = { 22, 110, 330, 800, 975, 1150, 0 };

	Property* prop = new Property(name, GlobalConstants::PropertyColors::BLUE, 150, 100, rent, 1);
	Property* prop2 = new Property("street2", GlobalConstants::PropertyColors::BLUE, 1500, 100, rent, 1);

	std::cout << prop->getName() << std::endl;
	std::cout << prop->getPriceForBuilding() << std::endl;
	std::cout << prop->getOwnerId() << std::endl;
	std::cout << prop->getRentPrice() << std::endl;

	Player* player = new Player("Ivan");

	std::cout << player->getCurrentPosition() << std::endl;
	std::cout << player->getMoney() << std::endl;

	player->addProperty(prop);

	std::cout << player->ownsProperty(prop2) << std::endl;
	std::cout << player->getMoney() << std::endl;

}                         