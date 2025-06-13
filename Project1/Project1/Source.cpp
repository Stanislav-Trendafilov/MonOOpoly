#include <iostream>
#include "Player.h"
#include "Property.h"
#include "MyString.h"
#include "Constants.h"
#include "Board.h"
#include "TrainStation.h"
#include "GoToJailField.h"
#include "MoveToLocationCard.h"
#include "PayFieldTax.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


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

	HeterogeneousContainer<Field> fields;

	int rent17[] = { 24, 120, 360, 850, 1025, 1200 };
	fields.addObject(new Property("Ancient Theatre Plovdiv", GlobalConstants::PropertyColors::YELLOW, 280, 150, rent17, 29));

	fields.addObject(GoToJailField("Jail", 30));

	int rent18[] = { 26, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Vitosha Mountain", GlobalConstants::PropertyColors::GREEN, 300, 200, rent18, 31));


	int rent19[] = { 26, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Seven Rila Lakes", GlobalConstants::PropertyColors::GREEN, 300, 200, rent19, 32));


	int trainStationRents[] = { 50,100,150,200 };

	fields.addObject(new TrainStation("Station asd", 200, trainStationRents, 33));

	int rent20[] = { 28, 150, 450, 1000, 1200, 1400 };
	fields.addObject(new Property("Belogradchik Rocks", GlobalConstants::PropertyColors::GREEN, 320, 200, rent20, 34));


	fields.addObject(new TrainStation("Station Plovdiv", 200, trainStationRents, 35));

	for (size_t i = 0; i < 7; i++)
	{
		std::cout<<fields[i]->getName()<<std::endl;
	}

	PayFieldTax* pay=new PayFieldTax("danaci", 36, 100);

	pay->ApplyAction(*player);

	std::cout << player->getMoney() << std::endl;

	Board* board = Board::getInstance();


	Player* player2 = new Player("Gosho");

	MoveToLocationCard* card = new MoveToLocationCard("Move to station", "100", 33);

	card->applyEffect(*player2);

	std::cout << player2->getCurrentPosition() << std::endl;
	std::cout << player2->getMoney() << std::endl;

	MoveToLocationCard* card2 = new MoveToLocationCard("Move to station", "100", 2);

	card2->applyEffect(*player2);

	std::cout << player2->getCurrentPosition() << std::endl;
	std::cout << player2->getMoney() << std::endl;

}          