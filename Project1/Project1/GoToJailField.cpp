#include "GoToJailField.h"

GoToJailField::GoToJailField(const MyString& name, int boardIndex)
	: Field(boardIndex, name)
{

};

void GoToJailField::ApplyAction(Player& player)
{
	std::cout << "You have been sent to jail! " << std::endl;
	player.goInPrison();
	player.moveToLocation(GlobalConstants::IN_JAIL_INDEX);
}

Field* GoToJailField::clone() const
{
	return new GoToJailField(*this);
}