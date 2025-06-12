#include "GoToJailField.h"
#include "Player.h"

GoToJailField::GoToJailField(const MyString& name, int boardIndex)
	: Field(boardIndex)
{
	this->name = name;
}

void GoToJailField::ApplyAction(Player& player)
{
	player.goInPrison();
}

MyString GoToJailField::getName() const
{
	return name;
};

Field* GoToJailField::clone() const
{
	return new GoToJailField(*this);
}