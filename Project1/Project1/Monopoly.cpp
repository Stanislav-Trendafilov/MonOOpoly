#include "Monopoly.h"

Monopoly::Monopoly()
{

}

Monopoly* Monopoly::instance = nullptr;

Monopoly* Monopoly::getInstance()
{
	if (!instance)
	{
		instance = new Monopoly();
	}
	return instance;
}

void Monopoly::destroyInstance()
{
	delete instance;
	instance = nullptr;
}