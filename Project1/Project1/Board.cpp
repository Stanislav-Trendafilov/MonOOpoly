#include "Board.h"
#include "TrainStation.h"
#include "GoToJailField.h"

Board::Board()
{

}

Board* Board::instance = nullptr;

void Board::InitializeBoard()
{
	int trainStationRents[] = { 50,100,150,200 };
	
	int rent1[] = { 2, 10, 30, 90, 160, 250 };
	fields.addObject(new Property("Knyaz Boris I Street", GlobalConstants::PropertyColors::BROWN, 60, 50, rent1, 1));

	// Adding chance card to the board

	int rent2[] = { 4, 20, 60, 180, 320, 450 };
	fields.addObject(new Property("Tsar Simeon Street", GlobalConstants::PropertyColors::BROWN, 60, 50, rent2, 3));

	// Adding income tax card to the board

	fields.addObject(new TrainStation("Station Burgas", 200, trainStationRents, 5));

	int rent3[] = { 6, 30, 90, 270, 400, 550 };
	fields.addObject(new Property("Graf Ignatiev Street", GlobalConstants::PropertyColors::CYAN, 100, 50, rent3,6));

	// Adding chance card to the board

	int rent4[] = { 6, 30, 90, 270, 400, 550 };
	fields.addObject(new Property("Shishman Street", GlobalConstants::PropertyColors::CYAN, 100, 50, rent4, 8));

	int rent5[] = { 8, 40, 100, 300, 450, 600 };
	fields.addObject(new Property("Patriarch Evtimiy Blvd", GlobalConstants::PropertyColors::CYAN, 120, 50, rent5, 9));

	//adding visit jail card to the board

	int rent6[] = { 10, 50, 150, 450, 625, 750 };
	fields.addObject(new Property("Slaveykov Square", GlobalConstants::PropertyColors::PINK, 140, 100, rent6, 11));

	// Adding VIK card to the board

	int rent7[] = { 10, 50, 150, 450, 625, 750 };
	fields.addObject(new Property("Hristo Botev Blvd", GlobalConstants::PropertyColors::PINK, 140, 100, rent7, 13));

	int rent8[] = { 12, 60, 180, 500, 700, 900 };
	fields.addObject(new Property("Rakovski Street", GlobalConstants::PropertyColors::PINK, 160, 100, rent8, 14));

	fields.addObject(new TrainStation("Station Sofia", 200, trainStationRents, 15));

	int rent9[] = { 14, 70, 200, 550, 750, 950 };
	fields.addObject(new Property("FMI Sofia University", GlobalConstants::PropertyColors::ORANGE, 180, 100, rent9, 16));

	// Adding chance card to the board

	int rent10[] = { 14, 70, 200, 550, 750, 950 };
	fields.addObject(new Property("Tsarigradsko Shose Blvd", GlobalConstants::PropertyColors::ORANGE, 180, 100, rent10, 18));

	int rent11[] = { 16, 80, 220, 600, 800, 1000 };
	fields.addObject(new Property("New BG University", GlobalConstants::PropertyColors::ORANGE, 200, 100, rent11, 19));

	//add free parking field 20

	int rent12[] = { 18, 90, 250, 700, 875, 1050 };
	fields.addObject(new Property("National Palace of Culture", GlobalConstants::PropertyColors::RED, 220, 150, rent12, 21));

	// Adding chance card to the board

	int rent13[] = { 18, 90, 250, 700, 875, 1050 };
	fields.addObject(new Property("Ivan Vazov National Theatre", GlobalConstants::PropertyColors::RED, 220, 150, rent13, 23));

	int rent14[] = { 20, 100, 300, 750, 925, 1100 };
	fields.addObject(new Property("Vasil Levski Monument", GlobalConstants::PropertyColors::RED, 240, 150, rent14,24));

	fields.addObject(new TrainStation("Station Varna", 200, trainStationRents, 25));

	int rent15[] = { 22, 110, 330, 800, 975, 1150 };
	fields.addObject(new Property("Sea Garden Varna", GlobalConstants::PropertyColors::YELLOW, 260, 150, rent15,26));

	int rent16[] = { 22, 110, 330, 800, 975, 1150 };
	fields.addObject(new Property("Old Town Plovdiv", GlobalConstants::PropertyColors::YELLOW, 260, 150, rent16, 27));

	//adding vik card to the board	  28

	int rent17[] = { 24, 120, 360, 850, 1025, 1200 };
	fields.addObject(new Property("Ancient Theatre Plovdiv", GlobalConstants::PropertyColors::YELLOW, 280, 150, rent17, 29));

	fields.addObject(GoToJailField("Jail", 30));

	int rent18[] = { 26, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Vitosha Mountain", GlobalConstants::PropertyColors::GREEN, 300, 200, rent18, 31));


	int rent19[] = { 26, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Seven Rila Lakes", GlobalConstants::PropertyColors::GREEN, 300, 200, rent19, 32));

	//adding chance card to the board 33

	int rent20[] = { 28, 150, 450, 1000, 1200, 1400 };
	fields.addObject(new Property("Belogradchik Rocks", GlobalConstants::PropertyColors::GREEN, 320, 200, rent20, 34));

	fields.addObject(new TrainStation("Station Plovdiv", 200, trainStationRents, 35));

	//adding chance card to the board 36

	int rent21[] = { 35, 175, 500, 1100, 1300, 1500 };
	fields.addObject(new Property("Old Town Nessebar", GlobalConstants::PropertyColors::BLUE, 350, 200, rent21, 37));

	//adding pay tax card to the board 38

	int rent22[] = { 50, 200, 600, 1400, 1700, 2000 };
	fields.addObject(new Property("Rila Monastery", GlobalConstants::PropertyColors::BLUE, 400, 200, rent22, 39));

	//add land on start field 0


}

Board* Board::getInstance()
{
	if (!instance)
	{
		instance = new Board();
	}
	return instance;
}

void Board::destroyInstance()
{
	delete instance;
	instance = nullptr;
}