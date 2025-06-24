#include "Board.h"
#include "windows.h"

using namespace std;

Board::Board()
{
	InitializeBoard();
}

Board* Board::instance = nullptr;

void Board::PrintBoard() const
{
	for (size_t i = 0; i < 11; i++)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | ";
	}
	std::cout << std::endl;

	for (size_t i = 39; i > 30; i--)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | " << std::setw(161) << std::left << " " << " | " << setw(18) << std::left << fields[50 - i]->getName() << " | " << std::endl;;

	}

	for (size_t i = 30; i >= 20; i--)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Board::PrintBoard(const MyVector<Player> players) const
{
	int playersCount = players.size();

	for (size_t i = 0; i < 11; i++)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < 11; i++) 
{
		MyString playerStr = "";
		for (size_t j = 0; j < playersCount; j++) 
		{
			if (players[j].getCurrentPosition() == i) 
			{
				playerStr += "P";
				playerStr += playerStr.toMyString(players[j].getPlayerId());
				playerStr += " ";

			}
		}
		std::cout << std::setw(15) << std::left << playerStr << " | ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < 202; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;

	for (size_t i = 39; i > 30; i--)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | " << std::setw(161) << std::left << " " << " | " << setw(18) << std::left << fields[50 - i]->getName() << " | " << std::endl;

		MyString playerStr = "";
		for (size_t j = 0; j < playersCount; j++)
		{
			if (players[j].getCurrentPosition() ==i)
			{
				playerStr += "P";
				playerStr += playerStr.toMyString(players[j].getPlayerId());
				playerStr += " ";

			}
		}

		MyString playerStr2 = "";
		for (size_t j = 0; j < playersCount; j++)
		{
			if (players[j].getCurrentPosition() == 50 - i)
			{
				playerStr2 += "P";
				playerStr2 += playerStr2.toMyString(players[j].getPlayerId());
				playerStr2 += " ";

			}
		}
		std::cout << std::setw(15) << std::left << playerStr << " | " << std::setw(161)
			<< std::left << " " << " | " << setw(18) << playerStr2 << " | " << std::endl;

		std::cout << std::setw(15) << std::left << "----------------|" << std::setw(163)
			<< std::left << " " << setw(18) << "|--------------------| " << std::endl;
	}

	for (size_t i = 30; i >= 20; i--)
	{
		std::cout << std::setw(15) << std::left << fields[i]->getName() << " | ";
	}
	std::cout << std::endl;

	for (size_t i = 30; i >= 20; i--)
	{
		MyString playerStr = "";
		for (size_t j = 0; j < playersCount; j++)
		{
			if (players[j].getCurrentPosition() == i)
			{
				playerStr += "P";
				playerStr += playerStr.toMyString(players[j].getPlayerId());
				playerStr += " ";

			}
		}
		std::cout << std::setw(15) << std::left << playerStr << " | ";
	}

	std::cout << std::endl;

	for (size_t i = 0; i < 202; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Board::activateFieldEffect(Player& player)
{
	fields[player.getCurrentPosition()]->getName();
	fields[player.getCurrentPosition()]->ApplyAction(player);
}

void Board::InitializeBoard()
{
	int trainStationRents[] = { 50,100,150,200 };

	fields.addObject(new StartField("Land On Go!", 0, 200));

	int rent1[] = { 2, 6, 10, 30, 90, 160, 250 };
	fields.addObject(new Property("Knyaz Boris Str", GlobalConstants::PropertyColors::BROWN, 60, 50, rent1, 1));

	fields.addObject(new CardField("Chest", 2, "chest"));

	int rent2[] = { 4, 10, 20, 60, 180, 320, 450 };
	fields.addObject(new Property("Seminary", GlobalConstants::PropertyColors::BROWN, 60, 50, rent2, 3));

	fields.addObject(new PayFieldTax("Income Taxes", 4, 100));

	fields.addObject(new TrainStation("Station Burgas", 200, trainStationRents, 5));

	int rent3[] = { 6,22, 30, 90, 270, 400, 550 };
	fields.addObject(new Property("Grafa Str", GlobalConstants::PropertyColors::CYAN, 100, 50, rent3, 6));

	fields.addObject(new CardField("Chance?", 7, "chance"));

	int rent4[] = { 6,22, 30, 90, 270, 400, 550 };
	fields.addObject(new Property("Shishman Str", GlobalConstants::PropertyColors::CYAN, 100, 50, rent4, 8));

	int rent5[] = { 8,30, 40, 100, 300, 450, 600 };
	fields.addObject(new Property("Sea Garden Burgas", GlobalConstants::PropertyColors::CYAN, 120, 50, rent5, 9));


	fields.addObject(new VisitField(10, "Visit Jail"));

	int rent6[] = { 10,30, 50, 150, 450, 625, 750 };
	fields.addObject(new Property("Slaveykov Square", GlobalConstants::PropertyColors::PINK, 140, 100, rent6, 11));

	fields.addObject(new CompanyField("Electric Company", 150, 12));

	int rent7[] = { 10,30, 50, 150, 450, 625, 750 };
	fields.addObject(new Property("Hristo Botev Blvd", GlobalConstants::PropertyColors::PINK, 140, 100, rent7, 13));

	int rent8[] = { 12,40, 60, 180, 500, 700, 900 };
	fields.addObject(new Property("Rakovski Str", GlobalConstants::PropertyColors::PINK, 160, 100, rent8, 14));

	fields.addObject(new TrainStation("Station Sofia", 200, trainStationRents, 15));

	int rent9[] = { 14,45, 70, 200, 550, 750, 950 };
	fields.addObject(new Property("Faculty of Math", GlobalConstants::PropertyColors::ORANGE, 180, 100, rent9, 16));

	fields.addObject(new CardField("Chest", 17, "chest"));

	int rent10[] = { 14,45, 70, 200, 550, 750, 950 };
	fields.addObject(new Property("Tsarigradsko Shose", GlobalConstants::PropertyColors::ORANGE, 180, 100, rent10, 18));

	int rent11[] = { 16,60, 80, 220, 600, 800, 1000 };
	fields.addObject(new Property("New BG University", GlobalConstants::PropertyColors::ORANGE, 200, 100, rent11, 19));

	fields.addObject(new VisitField(20, "Free Parking"));

	int rent12[] = { 18,75, 90, 250, 700, 875, 1050 };
	fields.addObject(new Property("Palace of Culture", GlobalConstants::PropertyColors::RED, 220, 150, rent12, 21));

	fields.addObject(new CardField("Chance?", 22, "chance"));

	int rent13[] = { 18,75, 90, 250, 700, 875, 1050 };
	fields.addObject(new Property("Sofia Theatre", GlobalConstants::PropertyColors::RED, 220, 150, rent13, 23));

	int rent14[] = { 20,85, 100, 300, 750, 925, 1100 };
	fields.addObject(new Property("Levski Monument", GlobalConstants::PropertyColors::RED, 240, 150, rent14, 24));

	fields.addObject(new TrainStation("Station Varna", 200, trainStationRents, 25));

	int rent15[] = { 22,90, 110, 330, 800, 975, 1150 };
	fields.addObject(new Property("Varna Garden", GlobalConstants::PropertyColors::YELLOW, 260, 150, rent15, 26));

	int rent16[] = { 22,90, 110, 330, 800, 975, 1150 };
	fields.addObject(new Property("Old Town", GlobalConstants::PropertyColors::YELLOW, 260, 150, rent16, 27));

	fields.addObject(new CompanyField("Water Supply", 150, 28));

	int rent17[] = { 24,100, 120, 360, 850, 1025, 1200 };
	fields.addObject(new Property("Ancient Theatre", GlobalConstants::PropertyColors::YELLOW, 280, 150, rent17, 29));

	fields.addObject(GoToJailField("Go To Jail", 30));

	int rent18[] = { 26,105, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Pamporovo", GlobalConstants::PropertyColors::GREEN, 300, 200, rent18, 31));


	int rent19[] = { 26,105, 130, 390, 900, 1100, 1275 };
	fields.addObject(new Property("Vitoshka Str", GlobalConstants::PropertyColors::GREEN, 300, 200, rent19, 32));

	fields.addObject(new CardField("Chest", 33, "chest"));

	int rent20[] = { 28,110, 150, 450, 1000, 1200, 1400 };
	fields.addObject(new Property("Belogradchik", GlobalConstants::PropertyColors::GREEN, 320, 200, rent20, 34));

	fields.addObject(new TrainStation("Station Plovdiv", 200, trainStationRents, 35));

	fields.addObject(new CardField("Chance?", 36, "chance"));

	int rent21[] = { 35,120, 175, 500, 1100, 1300, 1500 };
	fields.addObject(new Property("Nessebar", GlobalConstants::PropertyColors::BLUE, 350, 200, rent21, 37));

	fields.addObject(new PayFieldTax("Marriage Tax", 38, 200));

	int rent22[] = { 50,130, 200, 600, 1400, 1700, 2000 };
	fields.addObject(new Property("Rila Monastery", GlobalConstants::PropertyColors::BLUE, 400, 200, rent22, 39));

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