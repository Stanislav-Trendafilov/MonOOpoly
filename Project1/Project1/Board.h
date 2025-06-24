#pragma once
#include "Field.h"
#include "Player.h"
#include "MyVector.hpp"
#include "HeterogeneousContainer.hpp"
#include "CardDeck.h"
#include "CardField.h"
#include "TrainStation.h"
#include "PayFieldTax.h"
#include "VisitField.h"
#include "StartField.h"
#include "GoToJailField.h"
#include "CompanyField.h"
#include "Property.h"
#include <iomanip>
#include <fstream>

class Board
{
	Board();
	static Board* instance;
	HeterogeneousContainer<Field> fields;

public:
	void activateFieldEffect(Player& player);
	void InitializeBoard();
	void PrintBoard() const;
	void PrintBoard(const MyVector<Player> players) const;
	static Board* getInstance();
	static void destroyInstance();

	void saveToBinary(std::ofstream& ofs) const;
	void loadFromBinary(std::ifstream& ifs);
};

