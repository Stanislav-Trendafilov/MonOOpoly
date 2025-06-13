#include "Card.h"

Card::Card(const MyString& name, const MyString& effect)
{
	this->name = name;
	this->effect = effect;
};

MyString Card::getName() const
{
	return name;
}

MyString Card::getEffect() const
{
	return effect;
}


