#include "Board.h"

Board::Board()
{

}

Board* Board::instance = nullptr;

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