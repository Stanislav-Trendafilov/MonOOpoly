#include "GoToJailField.h"

GoToJailField::GoToJailField(const MyString& name, int boardIndex)
	: Field(boardIndex, name)
{

};

void GoToJailField::ApplyAction(Player& player)
{
	player.goInPrison();
}

Field* GoToJailField::clone() const
{
	return new GoToJailField(*this);
}